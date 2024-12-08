// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/CounterStrikeGameState.h"

#include "Net/UnrealNetwork.h"

void ACounterStrikeGameState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	//TODO:做成条件复制？
	DOREPLIFETIME(ACounterStrikeGameState, RedPlayers);
	DOREPLIFETIME(ACounterStrikeGameState, BluePlayers);
}

void ACounterStrikeGameState::UpdatePlayerTeam(ASurvivalPlayerState* Player)
{
	TArray<ASurvivalPlayerState*>& PreTeam = Player->GetTeam() == ETeam::ETeam_Blue ? RedPlayers : BluePlayers;
	TArray<ASurvivalPlayerState*>& NewTeam = Player->GetTeam() == ETeam::ETeam_Blue ? BluePlayers : RedPlayers;
	if (PreTeam.Contains(Player))
	{
		PreTeam.Remove(Player);
	}
	if (!NewTeam.Contains(Player))
	{
		NewTeam.Add(Player);
	}
	//在Server端更新一下数据
	OnRep_BluePlayers();
	OnRep_RedPlayers();
}

void ACounterStrikeGameState::OnRep_RedPlayers()
{
	OnRedTeamCountChangedDelegate.Broadcast(RedPlayers.Num());
}

void ACounterStrikeGameState::OnRep_BluePlayers()
{
	OnBlueTeamCountChangedDelegate.Broadcast(BluePlayers.Num());
}
