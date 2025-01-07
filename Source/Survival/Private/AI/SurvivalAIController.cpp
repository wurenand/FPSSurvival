// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/SurvivalAIController.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Perception/AIPerceptionComponent.h"

ASurvivalAIController::ASurvivalAIController()
{
	AIPerception = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("AIPerception"));
	AIPerception->OnTargetPerceptionUpdated.AddDynamic(this, &ASurvivalAIController::OnTargetPerceptionCallback);
}

void ASurvivalAIController::OnTargetPerceptionCallback(AActor* Actor, FAIStimulus Stimulus)
{
	//追踪玩家逻辑
	if (Actor->ActorHasTag(FName("Player")))
	{
		if (Stimulus.WasSuccessfullySensed())
		{
			GetBlackboardComponent()->SetValueAsObject(FName("TargetPlayer"), Actor);
		}
		else
		{
			//找不到玩家了
			FTimerHandle TimerHandle;
			FTimerDelegate TimerDelegate;
			TimerDelegate.BindLambda([&]()-> void
			{
				GetBlackboardComponent()->SetValueAsBool(FName("bShouldRoar"), true);
				GetBlackboardComponent()->SetValueAsObject(FName("TargetPlayer"), nullptr);
			});
			//3s后则放弃追逐
			GetWorld()->GetTimerManager().SetTimer(TimerHandle, TimerDelegate, 3.f, false);
		}
	}
}

void ASurvivalAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	RunBehaviorTree(BehaviorTree);
}
