// Fill out your copyright notice in the Description page of Project Settings.


#include "Ability/WeaponAbility.h"

#include "Actor/WeaponBase.h"
#include "Components/AbilityComponent.h"
#include "Library/DataHelperLibrary.h"

AWeaponAbility::AWeaponAbility()
{
	AbilityName =  TEXT("Weapon");
}

void AWeaponAbility::UpdateValues()
{
	Super::UpdateValues();
	//WeaponBase
	BaseDamage = AbilityComponent->WeaponInfo.BaseDamage;
	BaseFrequency = AbilityComponent->WeaponInfo.BaseShootingSpeed;
	BaseMag = AbilityComponent->WeaponInfo.BaseMagCount;
	//Mult
	FString ContextString;
	if (DataTableRow.AbilityCurveTable)
	{
		MagMult = DataTableRow.AbilityCurveTable->FindCurve(TEXT("MagMult"),ContextString)->Eval(Level);
		DamageMult = DataTableRow.AbilityCurveTable->FindCurve(TEXT("DamageMult"),ContextString)->Eval(Level);
		FrequencyMult = DataTableRow.AbilityCurveTable->FindCurve(TEXT("FrequencyMult"),ContextString)->Eval(Level);
	}
	OnMaxMagChanged.Broadcast(AbilityName, BaseMag * MagMult);
}
