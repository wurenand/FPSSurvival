// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "SurvivalAIController.generated.h"

struct FAIStimulus;
/**
 * Only On Server 负责运行行为树 感知组件。控制AI
 * 蓝图中配置感知组件，主要使用视觉
 */
UCLASS()
class SURVIVAL_API ASurvivalAIController : public AAIController
{
	GENERATED_BODY()

public:
	ASurvivalAIController();
	
protected:
	virtual void OnPossess(APawn* InPawn) override;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	TObjectPtr<UAIPerceptionComponent> AIPerception;
	UPROPERTY(EditAnywhere,Category = "AI")
	TObjectPtr<UBehaviorTree> BehaviorTree;

	UFUNCTION()
	void OnTargetPerceptionCallback(AActor* Actor,FAIStimulus Stimulus);
};
