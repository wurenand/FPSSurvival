// Fill out your copyright notice in the Description page of Project Settings.


#include "Survival/Public/Player/SurvivalPlayerState.h"

#include "Components/AbilityComponent.h"
#include "Game/CounterStrikeGameState.h"
#include "Net/UnrealNetwork.h"
#include "Player/SurvivalPlayerController.h"

ASurvivalPlayerState::ASurvivalPlayerState()
{
	AbilityComponent = CreateDefaultSubobject<UAbilityComponent>(TEXT("AbilityComponent"));
	AbilityComponent->SetIsReplicated(true);
}

void ASurvivalPlayerState::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(ASurvivalPlayerState, AbilityComponent);
	DOREPLIFETIME(ASurvivalPlayerState, Team);
}

UAbilityComponent* ASurvivalPlayerState::GetAbilityComponent() const
{
	return AbilityComponent;
}

void ASurvivalPlayerState::SRV_SetTeam_Implementation(ETeam NewTeam)
{
	if (Team == NewTeam)
	{
		return;
	}
	Team = NewTeam;
	//通知GameState队伍人数变化 On In CS Mode
	if (ACounterStrikeGameState* CounterStrikeGameState = Cast<ACounterStrikeGameState>(GetWorld()->GetGameState()))
	{
		CounterStrikeGameState->UpdatePlayerTeam(this);
	}
	//Spawn Player
	GetWorld()->GetAuthGameMode()->RestartPlayer(GetPlayerController());
	if (ASurvivalPlayerController* SurvivalPlayerController = Cast<ASurvivalPlayerController>(GetPlayerController()))
	{
		SurvivalPlayerController->ChangeOverlayPage(TEXT("PlayerUI"));
	}
}
