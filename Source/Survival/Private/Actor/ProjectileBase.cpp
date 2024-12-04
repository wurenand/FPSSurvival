#include "Actor/ProjectileBase.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"

AProjectileBase::AProjectileBase()
{
	PrimaryActorTick.bCanEverTick = true;
	ProjectileMesh = CreateDefaultSubobject<UStaticMeshComponent>("ProjectileMesh");
	ProjectileMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	SetRootComponent(ProjectileMesh);
	SphereCollision = CreateDefaultSubobject<USphereComponent>("SphereCollision");
	SphereCollision->SetCollisionProfileName("OverlapAllDynamic");
	SphereCollision->SetupAttachment(RootComponent);

	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement"));
	ProjectileMovement->ProjectileGravityScale = 0.f;
	SetReplicates(true);
}

void AProjectileBase::BeginPlay()
{
	Super::BeginPlay();
	SetLifeSpan(LifeSpan);
	SphereCollision->OnComponentBeginOverlap.AddDynamic(this,&AProjectileBase::OnHit);
	
	//做一些速度初始化，为什么不在构造函数做？...
	ProjectileMovement->Velocity = GetActorRotation().Vector() * InitialSpeed;
}

void AProjectileBase::OnHit(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (HasAuthority())
	{
		UE_LOG(LogTemp, Display, TEXT("OnHit Server"));
	}
	else
	{
		UE_LOG(LogTemp, Display, TEXT("OnHit Client"));
	}
}

