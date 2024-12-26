// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "SpawnProfileDataAsset.generated.h"
/**
 * 每个区间应当Spawn的信息
 */
USTRUCT(BlueprintType)
struct FIntervalSpawnParams
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, Category = "SpawnParams")
	int32 Interval = 0;
	//TODO:单独设置每个Class的Level
	//要Spawn的Actor的Level(如果有的话)
	UPROPERTY(EditAnywhere, Category = "SpawnParams")
	int32 Level = 0;
	//每个要Spawn的Actor的数量
	UPROPERTY(EditAnywhere, Category = "SpawnParams")
	TMap<TSubclassOf<AActor>, int32> ClassToCount;
};

/**
 * 采用区间Spawn方法。每个结构体包含一个区间长度，区间内的Spawn信息
 */
UCLASS()
class SURVIVAL_API USpawnProfileDataAsset : public UDataAsset
{
	GENERATED_BODY()

public:
	//最后一组会不断重复，如果没有则不会Spawn
	UPROPERTY(EditAnywhere, Category="SpawnProfile")
	TArray<FIntervalSpawnParams> Intervals;
};
