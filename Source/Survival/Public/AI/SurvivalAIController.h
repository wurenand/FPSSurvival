// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "SurvivalAIController.generated.h"

/**
 * 
 */
UCLASS()
class SURVIVAL_API ASurvivalAIController : public AAIController
{
	GENERATED_BODY()

protected:
	virtual void OnPossess(APawn* InPawn) override;

	UPROPERTY(EditAnywhere,Category = "AI")
	TObjectPtr<UBehaviorTree> BehaviorTree;
};
