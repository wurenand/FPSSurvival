// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PoolActor.h"
#include "CollisionInteractActorBase.generated.h"

class USphereComponent;
/**
 * TODO:作为可以与Player碰撞交互的基类
 */
UCLASS()
class SURVIVAL_API ACollisionInteractActorBase : public APoolActor
{
	GENERATED_BODY()
public:
	ACollisionInteractActorBase();
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Mesh")
	TObjectPtr<UStaticMeshComponent> StaticMesh;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Collision")
	TObjectPtr<USphereComponent> InteractCollision;

	UFUNCTION()
	virtual void OnInteractHit(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
					   int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	virtual void OnMeshHit(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
				   int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
};
