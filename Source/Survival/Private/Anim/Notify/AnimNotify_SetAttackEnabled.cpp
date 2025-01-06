// Fill out your copyright notice in the Description page of Project Settings.


#include "Anim/Notify/AnimNotify_SetAttackEnabled.h"

#include "Character/SurvivalEnemyCharacter.h"

void UAnimNotify_SetAttackEnabled::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::Notify(MeshComp, Animation);
	if (ASurvivalEnemyCharacter* EnemyCharacter = Cast<ASurvivalEnemyCharacter>(MeshComp->GetOwner()))
	{
		EnemyCharacter->Notify_SetEnableAttackCheck(bIsAttackEnabled);
	}
}
