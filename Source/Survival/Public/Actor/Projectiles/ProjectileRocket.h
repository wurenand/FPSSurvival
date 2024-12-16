// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actor/Projectiles/ProjectileBase.h"
#include "ProjectileRocket.generated.h"

/**
 * 
 */
UCLASS()
class SURVIVAL_API AProjectileRocket : public AProjectileBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere,Category = "ProjectileInfo")
	float Radius = 100.f;
	
protected:
	virtual void OnHit(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	                   int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;
};
