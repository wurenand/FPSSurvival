// Fill out your copyright notice in the Description page of Project Settings.


#include "Library/PoolHelperLibrary.h"
#include "Player/SurvivalPlayerState.h"

UObjectPoolComponent* UPoolHelperLibrary::GetProjectilePool(APlayerState* PlayerState, UClass* ProjectileClass)
{
	if (ASurvivalPlayerState* SurvivalPlayerState = Cast<ASurvivalPlayerState>(PlayerState))
	{
		return SurvivalPlayerState->GetPoolComponent(ProjectileClass);
	}
	return nullptr;
}
