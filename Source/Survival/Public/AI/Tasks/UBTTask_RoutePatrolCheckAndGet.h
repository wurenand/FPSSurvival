// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "UBTTask_RoutePatrolCheckAndGet.generated.h"

/**
 * 用于检测是否需要按照路线巡逻
 * 如果是，则获取下一个目标点或更新Index
 */
UCLASS()
class SURVIVAL_API UBTTask_RoutePatrolCheckAndGet : public UBTTaskNode
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(EditAnywhere,Category="Route")
	FBlackboardKeySelector KeyBShouldRandom;
	UPROPERTY(EditAnywhere,Category="Route")
	FBlackboardKeySelector KeyRouteIndex;
	UPROPERTY(EditAnywhere,Category="Route")
	FBlackboardKeySelector KeyTargetLocation;
	UPROPERTY(EditAnywhere,Category="Route")
	bool bUpdateIndex;
	UPROPERTY(EditAnywhere,Category="Route")
	float PatrolSpeed = 62.5f;
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
