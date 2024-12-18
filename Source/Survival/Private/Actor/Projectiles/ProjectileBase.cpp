#include "Actor/Projectiles/ProjectileBase.h"
#include "Character/SurvivalCharacterBase.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Interface/CombatInterface.h"
#include "Kismet/GameplayStatics.h"
#include "Net/UnrealNetwork.h"
#include "Particles/ParticleSystemComponent.h"
#include "Player/SurvivalPlayerController.h"

AProjectileBase::AProjectileBase()
{
	PrimaryActorTick.bCanEverTick = true;
	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);
	ProjectileMesh = CreateDefaultSubobject<UStaticMeshComponent>("ProjectileMesh");
	ProjectileMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	ProjectileMesh->SetupAttachment(Root);
	SphereCollision = CreateDefaultSubobject<USphereComponent>("SphereCollision");
	SphereCollision->SetCollisionEnabled(ECollisionEnabled::Type::QueryAndPhysics);
	SphereCollision->SetCollisionResponseToAllChannels(ECR_Overlap);
	SphereCollision->SetCollisionObjectType(ECC_Ability); //设置为ECC_Ability
	SphereCollision->SetCollisionResponseToChannel(ECC_Ability, ECR_Ignore);
	SphereCollision->SetupAttachment(RootComponent);

	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement"));
	ProjectileMovement->ProjectileGravityScale = 0.f;

	TrailSystemComponent = CreateDefaultSubobject<UParticleSystemComponent>("TrailSystemComponent");
	TrailSystemComponent->SetupAttachment(RootComponent);
	bReplicates = true;
	//因为使用ActorPool BeginPlay会对此调用，
	SphereCollision->OnComponentBeginOverlap.AddDynamic(this, &AProjectileBase::OnHit);
}

void AProjectileBase::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(AProjectileBase, InitialSpeed)
}

void AProjectileBase::OnRep_bIsEnable()
{
	Super::OnRep_bIsEnable();
	if (!bIsEnable)
	{
		ProjectileMovement->Velocity = FVector::ZeroVector;
		TrailSystemComponent->DeactivateImmediate();
	}
}

void AProjectileBase::Mult_PoolActorBeginPlay_Implementation()
{
	//做一些速度初始化，为什么不在构造函数做？...
	ProjectileMovement->Velocity = GetActorRotation().Vector() * InitialSpeed;
	TrailSystemComponent->Activate();
}

void AProjectileBase::OnHit(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                            UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
                            const FHitResult& SweepResult)
{
	if (ICombatInterface* CombatInterface = Cast<ICombatInterface>(OtherActor))
	{
		///同队伍的不作处理
		if (CombatInterface->GetCharacterTeam() == Cast<ASurvivalCharacterBase>(GetInstigator())->GetCharacterTeam())
		{
			return;
		}
	}
	//Spawn命中特效
	UGameplayStatics::SpawnEmitterAtLocation(this, ImpactParticle, ProjectileMesh->GetComponentLocation());
	//造成伤害
	if (HasAuthority())
	{
		UE_LOG(LogTemp, Display, TEXT("OnHit Server"));
		if (ICombatInterface* CombatInterface = Cast<ICombatInterface>(OtherActor))
		{
			CombatInterface->CombatTakeDamage(Cast<ASurvivalCharacterBase>(GetInstigator()), Damage);
			//通知开火者成功命中
			if (ASurvivalPlayerController* SurvivalPlayerController = Cast<ASurvivalPlayerController>(
				GetInstigator()->GetController()))
			{
				SurvivalPlayerController->CL_AttackHit();
			}
		}
		PoolDestroy();
	}
}
