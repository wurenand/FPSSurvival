// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "UBTTask_RandomPatrol.generated.h"

/**
 * 
 */
UCLASS()
class SURVIVAL_API UUBTTask_RandomPatrol : public UBTTaskNode
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float PatrolWalkSpeed = 62.5f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float RandomPatrolRadius = 500.f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FBlackboardKeySelector OutKeyTargetLocation;
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
