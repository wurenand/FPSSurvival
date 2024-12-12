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
class SURVIVAL_API UWeaponAbility : public UAbilityBase
{
	GENERATED_BODY()
public:
	FORCEINLINE float GetBaseMag() const{return BaseMag;}
	FORCEINLINE float GetMagMult() const{return MagMult;}
	UWeaponAbility();

	FOnAbilityValueChangedSignature OnMaxMagChanged;

	virtual void UpdateValues() override;
protected:
	UPROPERTY(VisibleAnywhere,Category = "Values")
	float BaseMag = 1.0f;
	UPROPERTY(VisibleAnywhere,Category = "Values")
	float MagMult = 1.0f;//弹药系数
};
