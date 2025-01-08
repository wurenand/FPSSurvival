// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "UBTTask_AttackPlayer.generated.h"

/**
 * 
 */
UCLASS()
class SURVIVAL_API UUBTTask_AttackPlayer : public UBTTaskNode
{
	GENERATED_BODY()
	
protected:
	//需要比Montage播放结束提前多少Finish Execute
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float DelayOffset = 0.f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TObjectPtr<UAnimMontage> MontageToPlay;
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

};
