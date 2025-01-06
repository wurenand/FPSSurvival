// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/SurvivalAIController.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "Perception/AIPerceptionComponent.h"

ASurvivalAIController::ASurvivalAIController()
{
	AIPerception = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("AIPerception"));
	AIPerception->OnTargetPerceptionUpdated.AddDynamic(this, &ASurvivalAIController::OnTargetPerceptionCallback);
}

void ASurvivalAIController::OnTargetPerceptionCallback(AActor* Actor, FAIStimulus Stimulus)
{
	if (Stimulus.WasSuccessfullySensed() && Actor->ActorHasTag(FName("Player")))
	{
		GetBlackboardComponent()->SetValueAsObject(FName("TargetPlayer"), Actor);
		//TODO：下面这个TargetLocation暂时无用
		GetBlackboardComponent()->SetValueAsVector(FName("TargetLocation"), Actor->GetActorLocation());
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

void ASurvivalAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	RunBehaviorTree(BehaviorTree);
}
