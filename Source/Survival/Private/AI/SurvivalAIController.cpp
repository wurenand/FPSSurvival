// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/SurvivalAIController.h"

#include "Perception/AIPerceptionComponent.h"

ASurvivalAIController::ASurvivalAIController()
{
	AIPerception = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("AIPerception"));
	AIPerception->OnTargetPerceptionUpdated.AddDynamic(this,&ASurvivalAIController::OnTargetPerceptionCallback);
}

void ASurvivalAIController::OnTargetPerceptionCallback(AActor* Actor, FAIStimulus Stimulus)
{
	
}

void ASurvivalAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	RunBehaviorTree(BehaviorTree);
}
