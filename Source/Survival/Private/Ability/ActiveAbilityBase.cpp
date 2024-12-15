// Fill out your copyright notice in the Description page of Project Settings.


#include "Ability/ActiveAbilityBase.h"

#include "Character/SurvivalPlayerCharacter.h"
#include "Components/AbilityComponent.h"
#include "Library/DataHelperLibrary.h"


void UActiveAbilityBase::UpdateValues()
{
	Super::UpdateValues();
	DataTableRow = UDataHelperLibrary::GetAbilityDataFromName(AbilityComponent->SurvivalPlayerCharacter, AbilityName);
	//尝试获取Frequency的值
	if (DataTableRow.AbilityCurveTable)
	{
		FString ContextString;
		FRealCurve* BaseCurve = DataTableRow.AbilityCurveTable->FindCurve(TEXT("BaseFrequency"), ContextString);
		FRealCurve* CurveMult = DataTableRow.AbilityCurveTable->FindCurve(TEXT("FrequencyMult"), ContextString);
		BaseFrequency = BaseCurve ? BaseCurve->Eval(Level) : 1;
		FrequencyMult = CurveMult ? CurveMult->Eval(Level) : 1;
	}
	//重设Timer
	if (ActiveTimerHandle.IsValid())
	{
		//BUG:由于UObject没有默认的WorldContext，所以不能GetWorld()拿到世界
		GetOuter()->GetWorld()->GetTimerManager().ClearTimer(ActiveTimerHandle);
	}
	FTimerDelegate ActiveDelegate;
	ActiveDelegate.BindUObject(this, &UActiveAbilityBase::TriggerActiveEvent);
	GetOuter()->GetWorld()->GetTimerManager().SetTimer(ActiveTimerHandle, ActiveDelegate, BaseFrequency * BaseFrequency, true);
}

void UActiveAbilityBase::TriggerActiveEvent()
{
	UE_LOG(LogTemp, Display, TEXT("TriggerActiveEvent"));
}
