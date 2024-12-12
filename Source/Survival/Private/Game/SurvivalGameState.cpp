// Fill out your copyright notice in the Description page of Project Settings.


#include "Survival/Public/Game/SurvivalGameState.h"

#include "Library/DataHelperLibrary.h"
#include "Net/UnrealNetwork.h"

void ASurvivalGameState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(ASurvivalGameState, XP);
	DOREPLIFETIME(ASurvivalGameState, Level);
}

void ASurvivalGameState::AddXP(int32 XPToAdd)
{
	int32 NewLevel = UDataHelperLibrary::GetLevelFromXP(this, XP + XPToAdd);
	int32 NumberOfDelta = NewLevel - Level;
	for (; NumberOfDelta > 0; NumberOfDelta--)
	{
		//TODO:AddLevel 执行升级逻辑
		Level++;
	}
	XP += XPToAdd;
}

void ASurvivalGameState::OnRep_XP()
{
}
