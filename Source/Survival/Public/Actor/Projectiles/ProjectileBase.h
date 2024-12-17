// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ObjectPoolInterface.h"
#include "GameFramework/Actor.h"
#include "ProjectileBase.generated.h"

class UProjectileMovementComponent;
class USphereComponent;

/**
 * 飞行物的Base，Instigator需要是PlayerCharacter
 */
UCLASS()
class SURVIVAL_API AProjectileBase : public AActor,public IObjectPoolInterface
{
public:
	GENERATED_BODY()
	
	FORCEINLINE void SetInitialSpeed(float InInitialSpeed)
	{
		this->InitialSpeed = InInitialSpeed;
	}

	FORCEINLINE void SetDamage(float InDamage)
	{
		this->Damage = InDamage;
	}
	
	AProjectileBase();
	virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;

	//~Begin IObjectPoolInterface
	virtual void SetEnableActor(bool bIsEnable) override;
	virtual void PoolDestroy() override;
	virtual void PoolActorBeginPlay_Implementation() override;
	//~End IObjectPoolInterface

	virtual void BeginPlay() override;
	
protected:
	UPROPERTY(EditAnywhere)
	TObjectPtr<USceneComponent> Root;
	UPROPERTY(EditAnywhere, Category = "Collsion")
	TObjectPtr<USphereComponent> SphereCollision;
	UPROPERTY(EditAnywhere, Category = "Mesh")
	TObjectPtr<UStaticMeshComponent> ProjectileMesh;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Movement")
	TObjectPtr<UProjectileMovementComponent> ProjectileMovement;

	//~Begin FX
	UPROPERTY(EditAnywhere,Category = "Effect")
	TObjectPtr<UParticleSystemComponent> TrailSystemComponent;//在编辑器中配置.
	UPROPERTY(EditAnywhere,Category = "Effect")
	TObjectPtr<UParticleSystem> ImpactParticle;//子弹命中的特效
	//~End

	UFUNCTION()
	virtual void OnHit(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	           int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	//下面的数据应当来自于Weapon  需要复制，不然Client的速度不同步
	UPROPERTY(BlueprintReadOnly,Replicated ,Category = "ProjectileInfo")
	float InitialSpeed = 500.f;
	UPROPERTY(BlueprintReadOnly, Category = "ProjectileInfo")
	float Damage = 10.f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ProjectileInfo")
	float LifeSpan = 5.f;

	//用于ActorPool
	UPROPERTY(ReplicatedUsing = OnRep_bIsEnable)
	bool bIsEnable = true;
	UFUNCTION()
	void OnRep_bIsEnable();
};
