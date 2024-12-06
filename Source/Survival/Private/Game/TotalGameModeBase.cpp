// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/TotalGameModeBase.h"

void ATotalGameModeBase::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);
	if (!ConnectedPlayers.Contains(NewPlayer))
	{
		ConnectedPlayers.Add(NewPlayer);
	}
}

void ATotalGameModeBase::Logout(AController* Exiting)
{
	Super::Logout(Exiting);
	if (ConnectedPlayers.Contains(Exiting))
	{
		ConnectedPlayers.Remove(Cast<APlayerController>(Exiting));
	}
}

void ATotalGameModeBase::PlayerEliminated(ASurvivalCharacterBase* EliminatedCharacter,
                                          ASurvivalPlayerController* VictimController,
                                          ASurvivalPlayerController* AttackerController)
{
}

void ATotalGameModeBase::RestartPlayer(AController* NewPlayer)
{
	Super::RestartPlayer(NewPlayer);
}
