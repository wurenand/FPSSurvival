// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Tasks/UBTTask_Roar.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Character/SurvivalEnemyCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"

class ASurvivalEnemyCharacter;

EBTNodeResult::Type UUBTTask_Roar::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	//是EnemyCharacter在使用
	if (ASurvivalEnemyCharacter* EnemyCharacter = Cast<ASurvivalEnemyCharacter>(OwnerComp.GetAIOwner()->GetPawn()))
	{
		EnemyCharacter->GetCharacterMovement()->MaxWalkSpeed = ChaseWalkSpeed;
		OwnerComp.GetBlackboardComponent()->SetValueAsBool(OutKeyBShouldRoar.SelectedKeyName, false);

		checkf(MontageToPlay, TEXT("UBTTask_Roar: MontageToPlay Is Null"));
		float Length = MontageToPlay->GetPlayLength();
		EnemyCharacter->Mult_PlayMontage(MontageToPlay);
		//用于等待Montage播放完成后再结束
		FTimerDelegate TimerDelegate;
		FTimerHandle TimerHandle;
		TimerDelegate.BindLambda([this,&OwnerComp]()-> void
		{
			FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
		});
		GetWorld()->GetTimerManager().SetTimer(TimerHandle, TimerDelegate, Length - DelayOffset, false);
		return EBTNodeResult::InProgress;
	}
	return EBTNodeResult::Failed;
}
