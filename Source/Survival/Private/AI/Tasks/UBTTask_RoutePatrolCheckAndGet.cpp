// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Tasks/UBTTask_RoutePatrolCheckAndGet.h"

#include "AIController.h"
#include "Actor/AIPatrolPathSpline.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Character/SurvivalEnemyCharacter.h"
#include "Components/SplineComponent.h"
#include "GameFramework/CharacterMovementComponent.h"


EBTNodeResult::Type UBTTask_RoutePatrolCheckAndGet::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	//是EnemyCharacter在使用
	if (ASurvivalEnemyCharacter* EnemyCharacter = Cast<ASurvivalEnemyCharacter>(OwnerComp.GetAIOwner()->GetPawn()))
	{
		EnemyCharacter->GetCharacterMovement()->MaxWalkSpeed = PatrolSpeed;
		//设定了巡逻路线
		if (EnemyCharacter->PatrolPathSpline)
		{
			int32 NumberOfPoints = EnemyCharacter->PatrolPathSpline->PathSplineComponent->GetNumberOfSplinePoints();
			int32 CurrentIndex = OwnerComp.GetBlackboardComponent()->GetValueAsInt(KeyRouteIndex.SelectedKeyName);
			//刚巡逻完一点，更新位置
			if (bUpdateIndex)
			{
				CurrentIndex++;
				CurrentIndex %= NumberOfPoints;
				if (CurrentIndex == 0)
				{
					//结束了一轮，可以开始随机休息了
					OwnerComp.GetBlackboardComponent()->SetValueAsBool(KeyBShouldRandom.SelectedKeyName, true);
				}
				OwnerComp.GetBlackboardComponent()->SetValueAsInt(KeyRouteIndex.SelectedKeyName, CurrentIndex);
			}
			//获取位置
			else
			{
				FVector Location = EnemyCharacter->PatrolPathSpline->PathSplineComponent->GetLocationAtSplinePoint(
					CurrentIndex, ESplineCoordinateSpace::Type::World);
				OwnerComp.GetBlackboardComponent()->SetValueAsVector(KeyTargetLocation.SelectedKeyName, Location);
			}
			return EBTNodeResult::Succeeded;
		}
		else
		{
			//没有设定巡逻路线 return Failed
			OwnerComp.GetBlackboardComponent()->SetValueAsBool(KeyBShouldRandom.SelectedKeyName, true);
		}
	}
	return EBTNodeResult::Failed;
}
