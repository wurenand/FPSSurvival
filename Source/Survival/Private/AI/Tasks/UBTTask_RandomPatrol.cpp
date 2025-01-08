// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Tasks/UBTTask_RandomPatrol.h"

#include "AIController.h"
#include "NavigationSystem.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BTFunctionLibrary.h"
#include "Character/SurvivalEnemyCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"

EBTNodeResult::Type UUBTTask_RandomPatrol::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	//是EnemyCharacter在使用
	if (ASurvivalEnemyCharacter* EnemyCharacter = Cast<ASurvivalEnemyCharacter>(OwnerComp.GetAIOwner()->GetPawn()))
	{
		EnemyCharacter->GetCharacterMovement()->MaxWalkSpeed = PatrolWalkSpeed;
		//确定存在NavMesh
		if (UNavigationSystemV1* NavSystem = FNavigationSystem::GetCurrent<UNavigationSystemV1>(GetWorld()))
		{
			FNavLocation OutTargetLoc;
			if (NavSystem->GetRandomReachablePointInRadius(EnemyCharacter->GetActorLocation(), RandomPatrolRadius,
			                                               OutTargetLoc))
			{
				OwnerComp.GetBlackboardComponent()->SetValueAsVector(OutKeyTargetLocation.SelectedKeyName,
				                                                     OutTargetLoc.Location);
				return EBTNodeResult::Succeeded;
			}
		}
	}
	return EBTNodeResult::Failed;
}
