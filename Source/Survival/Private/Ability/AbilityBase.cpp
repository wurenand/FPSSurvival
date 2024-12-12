// Fill out your copyright notice in the Description page of Project Settings.


#include "Ability/AbilityBase.h"

#include "Character/SurvivalPlayerCharacter.h"
#include "Components/AbilityComponent.h"
#include "Library/DataHelperLibrary.h"

void UAbilityBase::AddLevel()
{
	Level++;
	UpdateValues();
}

void UAbilityBase::UpdateValues()
{
	DataTableRow = UDataHelperLibrary::GetAbilityDataFromName(AbilityComponent->SurvivalPlayerCharacter,AbilityName);
}
