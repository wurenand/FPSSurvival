// Fill out your copyright notice in the Description page of Project Settings.


#include "Survival/Public/Player/SurvivalPlayerState.h"

#include "ObjectPoolComponent.h"
#include "ObjectPoolProfileDataAsset.h"
#include "Ability/SurvivalAbilitySystemComponent.h"
#include "Ability/SurvivalAttributeSet.h"
#include "Components/AbilityComponent.h"
#include "Game/CounterStrikeGameState.h"
#include "Net/UnrealNetwork.h"
#include "Player/SurvivalPlayerController.h"

ASurvivalPlayerState::ASurvivalPlayerState()
{
	AbilitySystemComponent = CreateDefaultSubobject<USurvivalAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	AbilitySystemComponent->SetIsReplicated(true);
	//Mixed 标识只会把GE复制到它的Owner处
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);
	//不需要复制，Attribute由AttributeSet负责复制，AttributeSet会自动注册到ASC中，默认就会复制
	AttributeSet = CreateDefaultSubobject<USurvivalAttributeSet>(TEXT("AttributeSet"));

	PoolComponent = CreateDefaultSubobject<UObjectPoolComponent>(TEXT("BulletPool"));
}

void ASurvivalPlayerState::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(ASurvivalPlayerState, Team);
}

UAbilitySystemComponent* ASurvivalPlayerState::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

USurvivalAttributeSet* ASurvivalPlayerState::GetSurvivalAttributeSet() const
{
	return AttributeSet;
}

void ASurvivalPlayerState::BeginPlay()
{
	Super::BeginPlay();
	if (HasAuthority())
	{
		PoolComponent->InitializeObjectPool(GetWorld());
	}
}

UObjectPoolComponent* ASurvivalPlayerState::GetPoolComponent(UClass* PoolActorClass) const
{
	if (PoolComponent->PoolData && PoolComponent->PoolData->PoolObjectClass == PoolActorClass)
	{
		return PoolComponent;
	}
	return nullptr;
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