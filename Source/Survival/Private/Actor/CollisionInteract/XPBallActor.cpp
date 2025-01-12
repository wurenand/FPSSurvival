#include "Actor/CollisionInteract/XPBallActor.h"
#include "Game/SurvivalGameState.h"

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
	if (!OtherActor->ActorHasTag("Player"))
	{
		return;
	}
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
