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

