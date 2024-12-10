// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/TotalGameModeBase.h"

#include "Game/TotalGameStateBase.h"

void ATotalGameModeBase::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);
	if (!ConnectedPlayers.Contains(NewPlayer))
	{
		ConnectedPlayers.Add(NewPlayer);
		//同步一下 GameState
		if (ATotalGameStateBase* GameStateBase = (GetGameState<ATotalGameStateBase>()))
		{
			GameStateBase->OnPlayerPostLogin(NewPlayer);
		}
	}
}

void ATotalGameModeBase::Logout(AController* Exiting)
{
	Super::Logout(Exiting);
	if (ConnectedPlayers.Contains(Exiting))
	{
		ConnectedPlayers.Remove(Cast<APlayerController>(Exiting));
		//同步一下 GameState
		if (ATotalGameStateBase* GameStateBase = (GetGameState<ATotalGameStateBase>()))
		{
			GameStateBase->OnPlayerLogout(Exiting);
		}
	}
}

void ATotalGameModeBase::PlayerEliminated(ASurvivalCharacterBase* EliminatedCharacter,
                                          ASurvivalPlayerController* VictimController,
                                          ASurvivalPlayerController* AttackerController)
{
	//子类去实现..
}
