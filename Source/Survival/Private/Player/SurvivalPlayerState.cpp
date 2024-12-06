// Fill out your copyright notice in the Description page of Project Settings.


#include "Survival/Public/Player/SurvivalPlayerState.h"

#include "Components/AbilityComponent.h"
#include "Net/UnrealNetwork.h"

ASurvivalPlayerState::ASurvivalPlayerState()
{
	AbilityComponent = CreateDefaultSubobject<UAbilityComponent	>(TEXT("AbilityComponent"));
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

