// Fill out your copyright notice in the Description page of Project Settings.


#include "Survival/Public/Player/SurvivalPlayerState.h"

#include "Components/AbilityComponent.h"

ASurvivalPlayerState::ASurvivalPlayerState()
{
	AbilityComponent = CreateDefaultSubobject<UAbilityComponent	>(TEXT("AbilityComponent"));
	AbilityComponent->SetIsReplicated(true);
}

UAbilityComponent* ASurvivalPlayerState::GetAbilityComponent() const
{
	return AbilityComponent;
}

