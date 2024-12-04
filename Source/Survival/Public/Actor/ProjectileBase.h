// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ProjectileBase.generated.h"

class UProjectileMovementComponent;
class USphereComponent;

UCLASS()
class SURVIVAL_API AProjectileBase : public AActor
{
public:
	FORCEINLINE void SetInitialSpeed(float InInitialSpeed)
	{
		this->InitialSpeed = InInitialSpeed;
	}

	FORCEINLINE void SetDamage(float InDamage)
	{
		this->Damage = InDamage;
	}

private:
	GENERATED_BODY()

public:
	AProjectileBase();
	virtual void BeginPlay() override;

protected:
	UPROPERTY(EditAnywhere, Category = "Collsion")
	TObjectPtr<USphereComponent> SphereCollision;
	UPROPERTY(EditAnywhere, Category = "Mesh")
	TObjectPtr<UStaticMeshComponent> ProjectileMesh;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Movement")
	TObjectPtr<UProjectileMovementComponent> ProjectileMovement;

	UFUNCTION()
	void OnHit(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	           int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	//下面的数据应当来自于Weapon
	UPROPERTY(BlueprintReadOnly, Category = "ProjectileInfo")
	float InitialSpeed = 500.f;
	UPROPERTY(BlueprintReadOnly, Category = "ProjectileInfo")
	float Damage = 10.f;
};
