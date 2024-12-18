// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PoolActor.generated.h"

class UObjectPoolComponent;

UCLASS()
class NPOBJECTPOOL_API APoolActor : public AActor
{
	GENERATED_BODY()

public:
	APoolActor();
	
	FORCEINLINE void SetPoolComponent(UObjectPoolComponent* InPool) { PoolComponent = InPool; };
	//开关Actor 通过Actor的bIsEnable复制变量，同步Server和Client  OnServer
	virtual void SetEnableActor(bool bInIsEnable);
	//PoolActor的销毁函数，主要就是DisableActor然后归还到Pool OnServer
	virtual void PoolDestroy();
	//PoolActor的BeginPlay，由使用者在拿到Actor并使用的最后调用 使用NetMult是确保所有实例都能调用BeginPlay
	UFUNCTION(NetMulticast, Reliable)
	void PoolActorBeginPlay(); //需要重写PoolActorBeginPlay_Implementation

	virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;

	UPROPERTY(EditAnywhere, Replicated, Category = "Pool")
	bool bUsePool = false;

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	//用于ActorPool
	UPROPERTY(VisibleAnywhere, ReplicatedUsing = OnRep_bIsEnable, Category = "Pool")
	bool bIsEnable = true;
	UFUNCTION()
	virtual void OnRep_bIsEnable();

	UPROPERTY(EditAnywhere, Category = "Pool")
	float PoolLifeSpan = 5.f;
	float PoolLifeSpanRemain = PoolLifeSpan;

	UPROPERTY()
	TObjectPtr<UObjectPoolComponent> PoolComponent;
};
