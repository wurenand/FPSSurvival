// Fill out your copyright notice in the Description page of Project Settings.


#include "Survival/Public/Player/SurvivalPlayerState.h"

#include "ObjectPoolComponent.h"
#include "ObjectPoolProfileDataAsset.h"
#include "Components/AbilityComponent.h"
#include "Game/CounterStrikeGameState.h"
#include "Net/UnrealNetwork.h"
#include "Player/SurvivalPlayerController.h"

ASurvivalPlayerState::ASurvivalPlayerState()
{
	AbilityComponent = CreateDefaultSubobject<UAbilityComponent>(TEXT("AbilityComponent"));
	AbilityComponent->SetIsReplicated(true);
	PoolComponent = CreateDefaultSubobject<UObjectPoolComponent>(TEXT("BulletPool"));
}

void ASurvivalPlayerState::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(ASurvivalPlayerState, AbilityComponent);
	DOREPLIFETIME(ASurvivalPlayerState, Team);
}

void ASurvivalPlayerState::BeginPlay()
{
	Super::BeginPlay();
	if (HasAuthority())
	{
		PoolComponent->InitializeObjectPool(GetWorld());
	}
}

UAbilityComponent* ASurvivalPlayerState::GetAbilityComponent() const
{
	return AbilityComponent;
}

UObjectPoolComponent* ASurvivalPlayerState::GetPoolComponent(UClass* PoolActorClass) const
{
	if (PoolComponent->PoolData && PoolComponent->PoolData->PoolObjectClass == PoolActorClass)
	{
		return PoolComponent;
	}
	return nullptr;
}

void ASurvivalPlayerState::TEST_GiveAbility(FName AbilityName)
{
	AbilityComponent->GiveAbility(AbilityName);
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
		SurvivalPlayerController->CL_ChangeOverlayPage(TEXT("PlayerUI"));
	}
}
