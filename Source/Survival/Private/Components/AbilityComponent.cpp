#include "Components/AbilityComponent.h"

#include "Ability/WeaponAbility.h"
#include "Character/SurvivalPlayerCharacter.h"
#include "Net/UnrealNetwork.h"

UAbilityComponent::UAbilityComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UAbilityComponent::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(UAbilityComponent,WeaponAbility);
}

float UAbilityComponent::GetShootFrequency()
{
	return GetWeaponAbility()->GetBaseFrequency() / GetWeaponAbility()->GetFrequencyMult();
}

float UAbilityComponent::GetShootDamage()
{
	return GetWeaponAbility()->GetBaseDamage() / GetWeaponAbility()->GetDamageMult();
}

void UAbilityComponent::TryLevelUpAbility(FName AbilityName)
{
	if (AbilityName == TEXT("Weapon"))
	{
		GetWeaponAbility()->AddLevel();
	}
}

void UAbilityComponent::BindAllValueDelegatesAndInit()
{
	//需要UI显示的就在这里绑定，不需要的就直接用函数返回
	//1. 绑定
	GetWeaponAbility()->OnMaxMagChanged.AddLambda([this](FName AbilityName, float NewValue)-> void
	{
		SurvivalPlayerCharacter->MaxMagCount = NewValue;
		SurvivalPlayerCharacter->OnRep_MaxMagCount();
	});

	//2. 获取值并广播
	GetWeaponAbility()->UpdateValues();
	for (auto Ability : ActiveAbilities)
	{
		Ability->UpdateValues();
	}
}

UWeaponAbility* UAbilityComponent::GetWeaponAbility()
{
	if (!WeaponAbility)
	{
		//初始化武器
		WeaponAbility = NewObject<UWeaponAbility>();
		WeaponAbility->AbilityComponent = this;
	}
	return WeaponAbility;
}
