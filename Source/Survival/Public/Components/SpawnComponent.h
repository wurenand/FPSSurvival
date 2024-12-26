// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Data/SpawnProfileDataAsset.h"
#include "SpawnComponent.generated.h"

class ATargetPoint;
class USpawnProfileDataAsset;
/**
 * Spawn系统核心
 */
UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class SURVIVAL_API USpawnComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	USpawnComponent();

	void StartSpawning();
	//停止区间后继续下一个
	void EndSpawningInterval();
	//停止区间不继续
	void EndSpawningAll();

protected:
	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
	//Spawn所依赖的配置表
	UPROPERTY(EditAnywhere, Category = "SpawnInfo")
	TObjectPtr<USpawnProfileDataAsset> SpawnProfile;
	//Spawn的位置 在里面随机选择
	UPROPERTY(VisibleAnywhere, Category = "GameInfo")
	TArray<AActor*> TargetPoints;

private:
	bool bIsSpawning = false;
	//处理当前Interval相关
	float IntervalCounter = 0.f;
	int32 CurrentIntervalIndex = 0;
	FIntervalSpawnParams CurrentSpawnParamsCopy;
	TArray<FTimerHandle> CurrentIntervalHandles;
};
