#pragma once

#include "CoreMinimal.h"
#include "PoolActor.h"
#include "GameFramework/Actor.h"
#include "XPBallActor.generated.h"

class USphereComponent;

UCLASS()
class SURVIVAL_API AXPBallActor : public APoolActor
{
	GENERATED_BODY()

public:
	AXPBallActor();

	FORCEINLINE void SetXP(int32 InXP) { XP = InXP; };

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Mesh")
	TObjectPtr<UStaticMeshComponent> BallMesh;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Collision")
	TObjectPtr<USphereComponent> InteractCollision;

	int32 XP = 0;

	//追踪
	bool bSetTargetActor = false;
	UPROPERTY()
	TObjectPtr<AActor> TargetActor = nullptr;
	
	virtual void OnRep_bIsEnable() override;
	
	UFUNCTION()
	void OnInteractHit(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	                   int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnMeshHit(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	               int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	virtual void Tick(float DeltaSeconds) override;
};
