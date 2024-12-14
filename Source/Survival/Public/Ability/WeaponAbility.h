// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Ability/AbilityBase.h"
#include "WeaponAbility.generated.h"

class AWeaponBase;
/**
 * 
 */
UCLASS()
class SURVIVAL_API AWeaponAbility : public AAbilityBase
{
	GENERATED_BODY()
public:
	MAKE_PUBLIC_VALUE_FUNCTIONS(BaseMag,MagMult)
	AWeaponAbility();

	FOnAbilityValueChangedSignature OnMaxMagChanged;

	virtual void UpdateValues() override;
protected:
	MAKE_VALUE(Mag)
};
