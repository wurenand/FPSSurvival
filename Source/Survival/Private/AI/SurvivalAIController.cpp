// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/SurvivalAIController.h"


void ASurvivalAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	RunBehaviorTree(BehaviorTree);
}
