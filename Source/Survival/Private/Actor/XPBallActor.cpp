#include "Actor/XPBallActor.h"
#include "Components/SphereComponent.h"
#include "Game/SurvivalGameState.h"
#include "Survival/Survival.h"

AXPBallActor::AXPBallActor()
{
	PrimaryActorTick.bCanEverTick = true;
	InteractCollision = CreateDefaultSubobject<USphereComponent>(TEXT("InteractComponent"));
	InteractCollision->SetCollisionObjectType(ECC_PlayerInteract);
	InteractCollision->SetCollisionResponseToAllChannels(ECR_Overlap);
	InteractCollision->SetCollisionResponseToChannel(ECC_PlayerInteract, ECR_Ignore);
	SetRootComponent(InteractCollision);
	BallMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BallMesh"));
	BallMesh->SetupAttachment(InteractCollision);
	BallMesh->SetCollisionObjectType(ECC_PlayerInteract);
	BallMesh->SetCollisionResponseToAllChannels(ECR_Overlap);
	BallMesh->SetCollisionResponseToChannel(ECC_PlayerInteract, ECR_Ignore);

	InteractCollision->OnComponentBeginOverlap.AddDynamic(this, &AXPBallActor::OnInteractHit);
	BallMesh->OnComponentBeginOverlap.AddDynamic(this, &AXPBallActor::OnMeshHit);
	bUseLifeSpan = false;
}

void AXPBallActor::OnRep_bIsEnable()
{
	Super::OnRep_bIsEnable();
	bSetTargetActor = false;
	TargetActor = nullptr;
}

void AXPBallActor::OnInteractHit(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                 UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
                                 const FHitResult& SweepResult)
{
	if (bSetTargetActor)
	{
		return;
	}
	bSetTargetActor = true;
	TargetActor = OtherActor;
}

void AXPBallActor::OnMeshHit(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                             UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
                             const FHitResult& SweepResult)
{
	if (HasAuthority())
	{
		if (ASurvivalGameState* GameState = GetWorld()->GetGameState<ASurvivalGameState>())
		{
			GameState->AddXP(XP);
		}
		PoolDestroy();
	}
}

void AXPBallActor::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	if (bSetTargetActor && TargetActor != nullptr)
	{
		const FVector& CurrentLocation = GetActorLocation();
		const FVector& TargetLocation = TargetActor->GetActorLocation();
		SetActorLocation(FMath::Lerp(CurrentLocation, TargetLocation, DeltaSeconds * 2.f));
	}
}
