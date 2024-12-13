// Fill out your copyright notice in the Description page of Project Settings.


#include "Ability/AbilityBase.h"

#include "Character/SurvivalPlayerCharacter.h"
#include "Components/AbilityComponent.h"
#include "Library/DataHelperLibrary.h"
#include "Net/UnrealNetwork.h"

void AAbilityBase::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(AAbilityBase,Level);
}

void AAbilityBase::AddLevel()
{
	Level++;
	OnRep_Level();
	UpdateValues();
}

void AAbilityBase::UpdateValues()
{
	DataTableRow = UDataHelperLibrary::GetAbilityDataFromName(AbilityComponent->SurvivalPlayerCharacter,AbilityName);
}

void AAbilityBase::OnRep_Level()
{
	
}

AAbilityBase::AAbilityBase()
{
	bReplicates = true;
}
