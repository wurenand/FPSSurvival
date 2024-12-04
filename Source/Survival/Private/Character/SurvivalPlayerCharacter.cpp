// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/SurvivalPlayerCharacter.h"

#include "InputActionValue.h"
#include "Actor/ProjectileBase.h"
#include "Actor/WeaponBase.h"
#include "Camera/CameraComponent.h"
#include "Chaos/PBDSuspensionConstraintData.h"
#include "Components/AbilityComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Library/DataHelperLibrary.h"
#include "Net/UnrealNetwork.h"
#include "Player/SurvivalPlayerState.h"

ASurvivalPlayerCharacter::ASurvivalPlayerCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->bUsePawnControlRotation = true; //让摄像机与Pawn相同旋转
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
		InitializeAbilityComponent();
	}
}

void ASurvivalPlayerCharacter::OnRep_Weapon()
{
	if (Weapon)
	{
		Weapon->EquipWeapon(this);
		Weapon->WeaponInfo = UDataHelperLibrary::GetWeaponInfoFromName(this, Weapon->WeaponName);
	}
}

void ASurvivalPlayerCharacter::InitializeAbilityComponent()
{
	if (HasAuthority())
	{
		checkf(AbilityComponent->WeaponClass, TEXT("AbilityComponent::WeaponClass is NULL"))
		FActorSpawnParameters SpawnParameters;
		SpawnParameters.Owner = GetController();
		//只在Server端生成，注意要给Weapon设置为复制，这样Client端才会同步生成
		Weapon = Cast<AWeaponBase>(
			GetWorld()->SpawnActor(AbilityComponent->WeaponClass, nullptr, nullptr, SpawnParameters));
		OnRep_Weapon();
		//TODO:在AbilityComponent中设置点委托，用于绑定来更新例如HP，射速等的数据
	}
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

void ASurvivalPlayerCharacter::HandleInputShootStarted(const FInputActionValue& Value)
{
	UE_LOG(LogTemp, Warning, TEXT("AASurvivalPlayerCharacter : Try Start SHOOT"));
	if (bIsReloading)
	{
		return;
	}
	SRV_ShootWeapon(true);
}


void ASurvivalPlayerCharacter::HandleInputShootCompleted(const FInputActionValue& Value)
{
	UE_LOG(LogTemp, Warning, TEXT("AASurvivalPlayerCharacter : Try End SHOOT"));
	SRV_ShootWeapon(false);
}


void ASurvivalPlayerCharacter::SRV_ShootWeapon_Implementation(bool bShouldShooting)
{
	if (bShouldShooting)
	{
		if (bIsShooting)
		{
			return;
		}
		float ShootSpeed = 1;
		//手动调用一次解决 玩家只按一次使得定时器迅速被清除导致的不能射击问题
		ShootWeaponLoop();
		GetWorld()->GetTimerManager().SetTimer(ShootTimer, this, &ASurvivalPlayerCharacter::ShootWeaponLoop, ShootSpeed,
		                                       true);
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
	PlayAnimMontage(Weapon->WeaponInfo.ShootMontage, 1);
}

void ASurvivalPlayerCharacter::ShootWeaponLoop()
{
	UE_LOG(LogTemp, Warning, TEXT("Shooing!!!"));
	Mult_ShootWeaponEffect(GetActorLocation());
	TSubclassOf<AProjectileBase> BulletClass = Weapon->WeaponInfo.BulletClass;
	checkf(BulletClass, TEXT("WeaponTable BulletClass is NULL"));
	FTransform BulletTransform = GetActorTransform();
	BulletTransform.SetLocation(BulletTransform.GetLocation() + GetActorForwardVector() * 20);
	//TODO:(后续，使用蒙太奇Event具体Spawn时机，Spawn的位置...)
	AProjectileBase* Projectile = GetWorld()->SpawnActorDeferred<AProjectileBase>(
		BulletClass, BulletTransform, GetController(), this, ESpawnActorCollisionHandlingMethod::AlwaysSpawn,
		ESpawnActorScaleMethod::MultiplyWithRoot);
	//TODO:这里可以配置数据
	Projectile->SetDamage(Weapon->WeaponInfo.BaseDamage);
	Projectile->SetInitialSpeed(500.f);
	Projectile->FinishSpawning(BulletTransform);
}
