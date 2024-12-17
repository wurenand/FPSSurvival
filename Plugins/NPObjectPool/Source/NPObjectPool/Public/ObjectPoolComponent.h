// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ObjectPoolComponent.generated.h"


class UObjectPoolProfileDataAsset;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class NPOBJECTPOOL_API UObjectPoolComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UObjectPoolComponent();
	
	/**
	 * 尝试请求Actor
	 * @return 
	 */
	AActor* RequestActorFromPool();

	void ReleaseActorToPool(AActor* ActorToRelease);
	
	void InitializeObjectPool(UWorld* InWorld,UObjectPoolProfileDataAsset* DataAsset);

protected:
	AActor* SpawnNewActor();
	
	UPROPERTY()
	TMap<TObjectPtr<AActor>,bool> ObjectMap;
	UPROPERTY()
	TObjectPtr<UWorld> World = nullptr;
	
	TObjectPtr<UObjectPoolProfileDataAsset> PoolData;
};
