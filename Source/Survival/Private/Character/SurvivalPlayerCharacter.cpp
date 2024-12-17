// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/SurvivalPlayerCharacter.h"

#include "InputActionValue.h"
#include "ObjectPoolComponent.h"
#include "PlayMontageCallbackProxy.h"
#include "Actor/Projectiles/ProjectileBase.h"
#include "Actor/WeaponBase.h"
#include "Camera/CameraComponent.h"
#include "Components/AbilityComponent.h"
#include "Game/TotalGameModeBase.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Library/DataHelperLibrary.h"
#include "Library/PoolHelperLibrary.h"
#include "Net/UnrealNetwork.h"
#include "Player/SurvivalPlayerController.h"
#include "Player/SurvivalPlayerState.h"
#include "UI/HUD/TotalHUD.h"

ASurvivalPlayerCharacter::ASurvivalPlayerCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->bUsePawnControlRotation = true; //让摄像机与PawnController相同旋转
	SpringArm->TargetArmLength = 0;
	SpringArm->SetupAttachment(GetMesh(), FName(TEXT("S_Camera")));

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);

	//第三人称Mesh，只用作显示影子使用！不能处理任何碰撞等..
	ThirdPersonMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("ThirdPersonMesh"));
	ThirdPersonMesh->SetupAttachment(GetMesh());
	ThirdPersonMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	ThirdPersonMesh->SetHiddenInGame(true);
	ThirdPersonMesh->SetCastHiddenShadow(true); //打开隐藏阴影，即使HideInGame也能投射Shadow
}

void ASurvivalPlayerCharacter::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(ASurvivalPlayerCharacter, Weapon);
	DOREPLIFETIME(ASurvivalPlayerCharacter, CurrentMagCount);
	DOREPLIFETIME(ASurvivalPlayerCharacter, MaxMagCount);
	DOREPLIFETIME(ASurvivalPlayerCharacter, AimDirection);
	DOREPLIFETIME(ASurvivalPlayerCharacter, bIsReloading);
	DOREPLIFETIME(ASurvivalPlayerCharacter, bIsShooting);
}

void ASurvivalPlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	//隐藏Mesh头部，避免遮挡射线机
	if (IsLocallyControlled())
	{
		GetMesh()->HideBoneByName(FName(TEXT("head")), PBO_None);
	}
}

void ASurvivalPlayerCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	HitTraceTick(DeltaSeconds);
}

void ASurvivalPlayerCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	if (ASurvivalPlayerState* SurvivalPlayerState = (GetController()->GetPlayerState<ASurvivalPlayerState>()))
	{
		AbilityComponent = SurvivalPlayerState->GetAbilityComponent();
		InitializeAbilityComponent();
	}
}

void ASurvivalPlayerCharacter::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();
	if (ASurvivalPlayerState* SurvivalPlayerState = Cast<ASurvivalPlayerState>(GetPlayerState()))
	{
		AbilityComponent = SurvivalPlayerState->GetAbilityComponent();
		Team = SurvivalPlayerState->GetTeam();
		InitializeAbilityComponent();
	}
}

void ASurvivalPlayerCharacter::InitUIValues()
{
	OnMaxMagCountChanged.Broadcast(MaxMagCount);
	OnMagCountChanged.Broadcast(CurrentMagCount);
	OnMaxHPChanged.Broadcast(MaxHealth);
	OnHPChanged.Broadcast(Health);
	OnIsAimingEnemyChanged.Broadcast(false);
}

void ASurvivalPlayerCharacter::OnRep_Weapon()
{
	if (Weapon)
	{
		//AttachWeapon到Character 并 获取配表中的信息
		Weapon->WeaponInfo = UDataHelperLibrary::GetWeaponInfoFromName(this, Weapon->WeaponName);
		AbilityComponent->WeaponInfo = Weapon->WeaponInfo;
		Weapon->EquipWeapon(this);
	}
}

void ASurvivalPlayerCharacter::InitializeAbilityComponent()
{
	AbilityComponent->SurvivalPlayerCharacter = this;
	if (HasAuthority())
	{
		checkf(AbilityComponent->WeaponClass, TEXT("AbilityComponent::WeaponClass is NULL"))
		FActorSpawnParameters SpawnParameters;
		SpawnParameters.Owner = GetController();
		//只在Server端生成，注意要给Weapon设置为复制，这样Client端才会同步生成
		Weapon = Cast<AWeaponBase>(
			GetWorld()->SpawnActor(AbilityComponent->WeaponClass, nullptr, nullptr, SpawnParameters));
		OnRep_Weapon();
		//TODO:AC这里会读表，并绑定回调用于更新Character的数值
		/**为什么这里只在Server端绑定呢？首先伤害计算是通过直接Get函数来获取的，而伤害只在Server计算，所以无所谓。
		 * 对于需要同步到客户端UI显示的：流程是，当Ac中的Ability等级变化时，会广播使得Character中的值变化，Server端的数值收到后，更新再复制给Client。
		 * 也就是说，可以直接使用Character里面的例如MaxMagCount的值，因为它已经与AC中的值同步了
		*/
		AbilityComponent->BindAllValueDelegatesAndInit();
		//初始化子弹值
		CurrentMagCount = MaxMagCount;
		OnRep_CurrentMagCount();
	}

	//如果有HUD，则更新其WidgetController中的Character参数
	if (IsLocallyControlled())
	{
		if (ASurvivalPlayerController* PlayerController = Cast<ASurvivalPlayerController>(GetController()))
		{
			ATotalHUD* TotalHUD = Cast<ATotalHUD>(PlayerController->GetHUD());
			TotalHUD->UpdateParamCharacter(this);
		}
	}
	//设置完UI之后广播初始值
	InitUIValues();
}

void ASurvivalPlayerCharacter::HandleInputMove(const FInputActionValue& Value)
{
	FVector2D MoveVector = Value.Get<FVector2D>();
	if (Controller)
	{
		AddMovementInput(GetActorForwardVector(), MoveVector.X);
		AddMovementInput(GetActorRightVector(), MoveVector.Y);
	}
}

void ASurvivalPlayerCharacter::HandleInputLook(const FInputActionValue& Value)
{
	FVector2D LookVector = Value.Get<FVector2D>();
	if (Controller)
	{
		AddControllerYawInput(LookVector.X);
		AddControllerPitchInput(-LookVector.Y);
	}
}

void ASurvivalPlayerCharacter::HandleInputJump(const FInputActionValue& Value)
{
	if (GetCharacterMovement()->CanEverJump())
	{
		Jump();
	}
}

void ASurvivalPlayerCharacter::HandleInputShootTriggered(const FInputActionValue& Value)
{
	if (bIsReloading)
	{
		return;
	}
	UE_LOG(LogTemp, Warning, TEXT("AASurvivalPlayerCharacter : Try Triggered SHOOT"));
	SRV_ShootWeapon(true, AimTargetPoint);
}


void ASurvivalPlayerCharacter::HandleInputShootCompleted(const FInputActionValue& Value)
{
	UE_LOG(LogTemp, Warning, TEXT("AASurvivalPlayerCharacter : Try End SHOOT"));
	SRV_ShootWeapon(false, AimTargetPoint);
}

void ASurvivalPlayerCharacter::HandleInputReload(const FInputActionValue& Value)
{
	if (bIsReloading)
	{
		return;
	}
	if (bIsShooting)
	{
		SRV_ShootWeapon(false, AimTargetPoint);
	}
	SRV_ReloadWeapon();
}

ETeam ASurvivalPlayerCharacter::GetCharacterTeam()
{
	if (ASurvivalPlayerState* SurvivalPlayerState = Cast<ASurvivalPlayerState>(GetPlayerState()))
	{
		if (Team != SurvivalPlayerState->GetTeam())
		{
			Team = SurvivalPlayerState->GetTeam();
		}
	}
	return Team;
}

void ASurvivalPlayerCharacter::CombatTakeDamage(ASurvivalCharacterBase* DamageInstigator, float DamageValue)
{
	//因为伤害只在Server处理。这个函数只在Server调用
	Health -= DamageValue;
	if (Health <= 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("AASurvivalPlayerCharacter : Die!!"));
		if (ATotalGameModeBase* TotalGameMode = Cast<ATotalGameModeBase>(GetWorld()->GetAuthGameMode()))
		{
			ASurvivalPlayerController* Victim = Cast<ASurvivalPlayerController>(GetController());
			ASurvivalPlayerController* Attacker = Cast<ASurvivalPlayerController>(DamageInstigator->GetController());
			TotalGameMode->PlayerEliminated(this, Victim, Attacker);
		}
	}
	//Server端BoardCast HP
	OnRep_Health();
	OnRep_MaxHealth();
}

void ASurvivalPlayerCharacter::SetPendingDeath(bool bQuickDestroy)
{
	if (bQuickDestroy)
	{
		if (Weapon)
		{
			Weapon->Destroy();
		}
		Destroy();
		return;
	}
	//Super负责多播特效
	Super::SetPendingDeath();
	FTimerDelegate DestroyDelegate;
	DestroyDelegate.BindLambda([this]()-> void
	{
		if (Weapon)
		{
			Weapon->Destroy();
		}
		Destroy();
	});
	FTimerHandle DestroyTimerHandle;
	GetWorld()->GetTimerManager().SetTimer(DestroyTimerHandle, DestroyDelegate, 3.0f, false);
}


void ASurvivalPlayerCharacter::SRV_ShootWeapon_Implementation(bool bShouldShooting, FVector LocalTargetPoint)
{
	if (bShouldShooting)
	{
		//接受从Client传递来的正确的瞄准位置
		AimTargetPoint = LocalTargetPoint;
		//如果启动了Timer就不要再次启动了，但是AimTargetPoint需要更新
		if (bIsShooting || bIsReloading)
		{
			return;
		}
		//手动调用一次解决 玩家只按一次使得定时器迅速被清除导致的不能射击问题
		ShootWeaponLoop();
		GetWorld()->GetTimerManager().SetTimer(ShootTimer, this, &ASurvivalPlayerCharacter::ShootWeaponLoop,
		                                       AbilityComponent->GetShootFrequency(), true);
		bIsShooting = true;
	}
	else
	{
		if (ShootTimer.IsValid())
		{
			GetWorld()->GetTimerManager().ClearTimer(ShootTimer);
			bIsShooting = false;
		}
	}
}

void ASurvivalPlayerCharacter::Mult_ShootWeaponEffect_Implementation(FVector Location)
{
	//特效，Montage，音效等
	if (bIsReloading)
	{
		return;
	}
	//这里可以用真实的射击速度来播放，但是没必要
	PlayAnimMontage(Weapon->WeaponInfo.ShootMontage, 1);
	Weapon->HandleShootEffect();
}

void ASurvivalPlayerCharacter::OnRep_CurrentMagCount()
{
	OnMagCountChanged.Broadcast(CurrentMagCount);
}

void ASurvivalPlayerCharacter::OnRep_MaxMagCount()
{
	OnMaxMagCountChanged.Broadcast(MaxMagCount);
}

void ASurvivalPlayerCharacter::ShootWeaponLoop()
{
	if (CurrentMagCount <= 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("NeedReload"));
		return;
	}
	CurrentMagCount--;
	OnRep_CurrentMagCount();
	UE_LOG(LogTemp, Warning, TEXT("Shooing!!! MagLeft %d"), CurrentMagCount);
	//Effect
	Mult_ShootWeaponEffect(GetActorLocation());

	TSubclassOf<AProjectileBase> BulletClass = Weapon->WeaponInfo.BulletClass;
	checkf(BulletClass, TEXT("WeaponTable BulletClass is NULL"));
	FTransform BulletTransform;
	FVector SpawnLocation = Weapon->GetWeaponMesh()->GetSocketLocation(TEXT("S_Muzzle"));
	FRotator SpawnRotator = (AimTargetPoint - SpawnLocation).Rotation();
	BulletTransform.SetLocation(SpawnLocation);
	BulletTransform.SetRotation(SpawnRotator.Quaternion());

	bool bUsePool = false;
	AProjectileBase* Projectile = nullptr;
	if (UObjectPoolComponent* ProjectilePoolComponent = UPoolHelperLibrary::GetPoolFromActorClass(
		this, AProjectileBase::StaticClass()))
	{
		bUsePool = true;
		Projectile = Cast<AProjectileBase>(ProjectilePoolComponent->RequestActorFromPool());
	}
	else
	{
		Projectile = GetWorld()->SpawnActorDeferred<AProjectileBase>(
			BulletClass, BulletTransform, GetController(), this, ESpawnActorCollisionHandlingMethod::AlwaysSpawn,
			ESpawnActorScaleMethod::MultiplyWithRoot);
	}

	//TODO:这里可以配置数据
	Projectile->SetDamage(AbilityComponent->GetShootDamage());
	Projectile->SetInitialSpeed(Weapon->WeaponInfo.BulletSpeed);
	Projectile->SetInstigator(this);
	if (bUsePool)
	{
		Projectile->SetActorTransform(BulletTransform);
		Cast<IObjectPoolInterface>(Projectile)->PoolActorBeginPlay();
	}
	else
	{
		Projectile->FinishSpawning(BulletTransform);
	}
}


void ASurvivalPlayerCharacter::Mult_ReloadWeaponEffect_Implementation()
{
	//TODO:后续改成MontageEvent？
	ReloadMontageProxy = nullptr; //让GC回收之前的对象
	ReloadMontageProxy = UPlayMontageCallbackProxy::CreateProxyObjectForPlayMontage(
		GetMesh(), Weapon->WeaponInfo.ReloadMontage, 1);
	if (ReloadMontageProxy)
	{
		ReloadMontageProxy->OnNotifyBegin.AddDynamic(this, &ASurvivalPlayerCharacter::OnReceiveMontageNotifyBegin);
		ReloadMontageProxy->OnCompleted.AddDynamic(this, &ASurvivalPlayerCharacter::OnReceiveMontageCompleted);
	}
}

void ASurvivalPlayerCharacter::SRV_ReloadWeapon_Implementation()
{
	if (!bIsReloading)
	{
		bIsReloading = true;
		Mult_ReloadWeaponEffect();
	}
}


void ASurvivalPlayerCharacter::HitTraceTick(float DeltaSeconds)
{
	HitTickCount += DeltaSeconds;
	FVector ViewLocation;
	FRotator ViewRotation;
	//只在本地获取AimDirection
	if (!GetController() || !IsLocallyControlled())
	{
		return;
	}
	GetController()->GetPlayerViewPoint(ViewLocation, ViewRotation);
	AimTargetPoint = ViewLocation + ViewRotation.Vector() * AimLength;
	if (HitTickCount >= HitTickFrequency)
	{
		HitTickCount = 0;

		FCollisionQueryParams CollisionParams;
		CollisionParams.AddIgnoredActor(this);
		GetWorld()->LineTraceSingleByChannel(HitTraceResult, ViewLocation, AimTargetPoint, ECC_Pawn, CollisionParams);

		if (ICombatInterface* CombatInterface = Cast<ICombatInterface>(HitTraceResult.GetActor()))
		{
			if (CombatInterface->GetCharacterTeam() != GetCharacterTeam())
			{
				OnIsAimingEnemyChanged.Broadcast(1);
				return;
			}
		}
		OnIsAimingEnemyChanged.Broadcast(0);
	}
}

void ASurvivalPlayerCharacter::Mult_DeathEffect_Implementation()
{
	Super::Mult_DeathEffect_Implementation();
	ThirdPersonMesh->SetCastHiddenShadow(false);
}

void ASurvivalPlayerCharacter::OnReceiveMontageNotifyBegin(FName NotifyName)
{
	if (NotifyName.IsEqual(TEXT("ClipOut")))
	{
		Weapon->GetWeaponMesh()->HideBoneByName(Weapon->WeaponInfo.MagBoneName, PBO_None);
	}
	if (NotifyName.IsEqual(TEXT("ClipIn")))
	{
		Weapon->GetWeaponMesh()->UnHideBoneByName(Weapon->WeaponInfo.MagBoneName);
	}
}

void ASurvivalPlayerCharacter::OnReceiveMontageCompleted(FName NotifyName)
{
	if (bIsReloading && HasAuthority())
	{
		CurrentMagCount = MaxMagCount;
		OnRep_CurrentMagCount();
		bIsReloading = false;
	}
}
