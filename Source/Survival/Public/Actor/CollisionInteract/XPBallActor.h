#pragma once

#include "CoreMinimal.h"
#include "CollisionInteractActorBase.h"
#include "GameFramework/Actor.h"
#include "XPBallActor.generated.h"

class USphereComponent;

UCLASS()
class SURVIVAL_API AXPBallActor : public ACollisionInteractActorBase
{
	GENERATED_BODY()

public:
	FORCEINLINE void SetXP(int32 InXP) { XP = InXP; };

protected:
	int32 XP = 0;

	//追踪
	bool bSetTargetActor = false;
	UPROPERTY()
	TObjectPtr<AActor> TargetActor = nullptr;

	virtual void OnRep_bIsEnable() override;

	virtual void Tick(float DeltaSeconds) override;

	virtual void OnMeshHit(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	                       int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;
	virtual void OnInteractHit(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	                           UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
	                           const FHitResult& SweepResult) override;
};
