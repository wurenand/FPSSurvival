// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "ObjectPoolProfileDataAsset.generated.h"

/**
 * 
 */
UCLASS()
class NPOBJECTPOOL_API UObjectPoolProfileDataAsset : public UDataAsset
{
	GENERATED_BODY()

public:
	//ObjectPool中实际存放的Actor类 需要实现ObjectPoolInterface
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="ObjectPool")
	TSubclassOf<AActor> PoolObjectClass;
	//初始时Spawn的Object对象
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="ObjectPool")
	int32 InitialObjectCount = 0;
	//这个Pool能容纳的最大对象
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="ObjectPool")
	int32 MaxObjectCount = 10;
};
