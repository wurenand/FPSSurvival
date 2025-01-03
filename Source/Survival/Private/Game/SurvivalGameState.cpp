// Fill out your copyright notice in the Description page of Project Settings.


#include "Survival/Public/Game/SurvivalGameState.h"

#include "Game/SurvivalGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "Library/DataHelperLibrary.h"
#include "Net/UnrealNetwork.h"

void ASurvivalGameState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(ASurvivalGameState, XP);
	DOREPLIFETIME(ASurvivalGameState, Level);
	DOREPLIFETIME(ASurvivalGameState, bIsPaused);
}

void ASurvivalGameState::SetAllGamePause(bool Pause)
{
	bIsPaused = Pause;
	OnRep_bIsPaused();
}

//Only Called On Server
void ASurvivalGameState::AddXP(int32 XPToAdd)
{
	int32 NewLevel = UDataHelperLibrary::GetLevelFromXP(this, XP + XPToAdd);
	int32 NumberOfDelta = NewLevel - Level;
	for (; NumberOfDelta > 0; NumberOfDelta--)
	{
		//TODO:AddLevel 执行升级逻辑
		Level++;
		OnRep_Level();
		Cast<ASurvivalGameMode>(GetWorld()->GetAuthGameMode())->LevelUp();
		SetAllGamePause(true);
	}
	XP += XPToAdd;
	OnRep_XP();
}

void ASurvivalGameState::OnRep_XP()
{
	//计算当前百分比
	OnXPPercentChanged.Broadcast(UDataHelperLibrary::GetPercentToNextLevelFromXP(this, XP));
}

void ASurvivalGameState::OnRep_Level()
{
	OnLevelChanged.Broadcast(Level);
}

void ASurvivalGameState::OnRep_bIsPaused()
{
	UGameplayStatics::SetGamePaused(GetWorld(), bIsPaused);
}
