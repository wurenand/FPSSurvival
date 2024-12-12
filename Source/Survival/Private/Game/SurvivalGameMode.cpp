// Fill out your copyright notice in the Description page of Project Settings.


#include "Survival/Public/Game/SurvivalGameMode.h"

#include "Game/SurvivalGameState.h"

void ASurvivalGameMode::PlayerEliminated(ASurvivalCharacterBase* EliminatedCharacter,
                                         ASurvivalPlayerController* VictimController, ASurvivalPlayerController* AttackerController)
{
	
}

void ASurvivalGameMode::EnemyEliminated(ASurvivalCharacterBase* EliminatedCharacter,
	ASurvivalPlayerController* AttackerController)
{
	//TODO:Spawn经验球
	
}

ASurvivalGameState* ASurvivalGameMode::GetGameState()
{
	if (!SurvivalGameState)
	{
		SurvivalGameState = Cast<ASurvivalGameState>(GetGameState());
	}
	return SurvivalGameState;
}
