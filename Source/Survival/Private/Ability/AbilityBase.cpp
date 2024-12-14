// Fill out your copyright notice in the Description page of Project Settings.


#include "Ability/AbilityBase.h"

#include "Character/SurvivalPlayerCharacter.h"
#include "Components/AbilityComponent.h"
#include "Library/DataHelperLibrary.h"
#include "Net/UnrealNetwork.h"

void AAbilityBase::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(AAbilityBase, Level);
}

void AAbilityBase::AddLevel()
{
	Level++;
	OnRep_Level();
	UpdateValues();
}


void AAbilityBase::UpdateValues()
{
	DataTableRow = UDataHelperLibrary::GetAbilityDataFromName(AbilityComponent->SurvivalPlayerCharacter, AbilityName);
	//尝试获取General的值
	if (DataTableRow.AbilityCurveTable)
	{
		FString ContextString;
		FRealCurve* BaseCurve = DataTableRow.AbilityCurveTable->FindCurve(TEXT("BaseGeneral"), ContextString);
		FRealCurve* CurveMult = DataTableRow.AbilityCurveTable->FindCurve(TEXT("GeneralMult"), ContextString);
		BaseGeneral = BaseCurve ? BaseCurve->Eval(Level) : 0;
		GeneralMult = CurveMult ? CurveMult->Eval(Level) : 0;
	}
	OnGeneralValueChanged.Broadcast(AbilityName, BaseGeneral * GeneralMult);
}

void AAbilityBase::OnRep_Level()
{
}

AAbilityBase::AAbilityBase()
{
	bReplicates = true;
	bAlwaysRelevant = true;
}
