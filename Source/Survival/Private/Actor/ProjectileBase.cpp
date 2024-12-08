#include "Actor/ProjectileBase.h"

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
	SphereCollision->SetCollisionEnabled(ECollisionEnabled::Type::QueryOnly);
	SphereCollision->SetCollisionResponseToAllChannels(ECR_Overlap);
	SphereCollision->SetCollisionObjectType(ECC_Ability);//设置为ECC_Ability
	SphereCollision->SetupAttachment(RootComponent);

	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement"));
	ProjectileMovement->ProjectileGravityScale = 0.f;

	TrailSystemComponent = CreateDefaultSubobject<UParticleSystemComponent>("TrailSystemComponent");
	TrailSystemComponent->SetupAttachment(RootComponent);
	SetReplicates(true);
}

void AProjectileBase::BeginPlay()
{
	Super::BeginPlay();
	SetLifeSpan(LifeSpan);
	SphereCollision->OnComponentBeginOverlap.AddDynamic(this, &AProjectileBase::OnHit);

	//做一些速度初始化，为什么不在构造函数做？...
	ProjectileMovement->Velocity = GetActorRotation().Vector() * InitialSpeed;
}

void AProjectileBase::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(AProjectileBase, InitialSpeed);
}

void AProjectileBase::OnHit(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                            UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
                            const FHitResult& SweepResult)
{
	//Spawn命中特效
	UGameplayStatics::SpawnEmitterAtLocation(this, ImpactParticle,ProjectileMesh->GetComponentLocation() );
	//通知开火者成功命中
	if(ASurvivalPlayerController* SurvivalPlayerController = Cast<ASurvivalPlayerController>(GetInstigator()->GetController()))
	{
		SurvivalPlayerController->CL_AttackHit();
	}
	//造成伤害
	if (HasAuthority())
	{
		UE_LOG(LogTemp, Display, TEXT("OnHit Server"));
		if (ICombatInterface* CombatInterface = Cast<ICombatInterface>(OtherActor))
		{
			CombatInterface->CombatTakeDamage(Cast<ASurvivalCharacterBase>(GetInstigator()), Damage);
		}
		Destroy();
	}
}
