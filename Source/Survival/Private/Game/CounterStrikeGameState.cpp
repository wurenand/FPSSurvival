// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/CounterStrikeGameState.h"

#include "Net/UnrealNetwork.h"
#include "Player/SurvivalPlayerController.h"

void ACounterStrikeGameState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	//TODO:做成条件复制？
	DOREPLIFETIME(ACounterStrikeGameState, RedPlayers);
	DOREPLIFETIME(ACounterStrikeGameState, RedDeadPlayers);
	DOREPLIFETIME(ACounterStrikeGameState, BluePlayers);
	DOREPLIFETIME(ACounterStrikeGameState, BlueDeadPlayers);
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

bool ACounterStrikeGameState::IsRoundOver(ASurvivalPlayerController* DeadPC)
{
	if (ASurvivalPlayerState* PlayerState = DeadPC->GetPlayerState<ASurvivalPlayerState>())
	{
		TArray<ASurvivalPlayerState*>& DeadTeam = PlayerState->GetTeam() == ETeam::ETeam_Blue
			                                          ? BlueDeadPlayers
			                                          : RedDeadPlayers;
		TArray<ASurvivalPlayerState*>& AllTeam = PlayerState->GetTeam() == ETeam::ETeam_Blue ? BluePlayers : RedPlayers;
		if (!DeadTeam.Contains(PlayerState))
		{
			DeadTeam.Add(PlayerState);
		}
		//Check Is Round Over?
		if (AllTeam.Num() == DeadTeam.Num())
		{
			//TODO：这里记录分数变化
			return true;
		}
	}
	return false;
}

void ACounterStrikeGameState::OnRep_RedPlayers()
{
	OnRedTeamCountChangedDelegate.Broadcast(RedPlayers.Num());
}

void ACounterStrikeGameState::OnRep_RedDeadPlayers()
{
}

void ACounterStrikeGameState::OnRep_BlueDeadPlayers()
{
}

void ACounterStrikeGameState::OnRep_BluePlayers()
{
	OnBlueTeamCountChangedDelegate.Broadcast(BluePlayers.Num());
}
