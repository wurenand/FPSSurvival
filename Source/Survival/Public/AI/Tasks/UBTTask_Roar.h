// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "UBTTask_Roar.generated.h"

/**
 * 
 */
UCLASS()
class SURVIVAL_API UUBTTask_Roar : public UBTTaskNode
{
	GENERATED_BODY()
	
protected:
	//需要比Montage播放结束提前多少Finish Execute
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float DelayOffset = 0.f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float ChaseWalkSpeed = 250.f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TObjectPtr<UAnimMontage> MontageToPlay;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FBlackboardKeySelector OutKeyBShouldRoar;
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
