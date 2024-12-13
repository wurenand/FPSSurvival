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
	DOREPLIFETIME(UAbilityComponent, WeaponAbility);
	DOREPLIFETIME(UAbilityComponent, OwnerPlayerState);
	DOREPLIFETIME(UAbilityComponent, ActiveAbilities);
}

float UAbilityComponent::GetShootFrequency()
{
	if (WeaponAbility == nullptr)
	{
		return 1.f;
	}
	return WeaponAbility->GetBaseFrequency() / WeaponAbility->GetFrequencyMult();
}

float UAbilityComponent::GetShootDamage()
{
	if (WeaponAbility == nullptr)
	{
		return 1.f;
	}
	return WeaponAbility->GetBaseDamage() / WeaponAbility->GetDamageMult();
}

void UAbilityComponent::TryLevelUpAbility(FName AbilityName)
{
	if (AbilityName == TEXT("Weapon"))
	{
		if (WeaponAbility == nullptr)
		{
			Mult_GiveAbility(TEXT("Weapon"), nullptr);
			return;
		}
		WeaponAbility->AddLevel();
	}
	else
	{
	}
}

void UAbilityComponent::Mult_GiveAbility_Implementation(FName AbilityName, TSubclassOf<UAbilityBase> AbilityClass)
{
	if (AbilityName == TEXT("Weapon"))
	{
		WeaponAbility = NewObject<UWeaponAbility>();
		WeaponAbility->AbilityComponent = this;
	}
	else
	{
		UAbilityBase* NewAbility = NewObject<UAbilityBase>(GetTransientPackage(),AbilityClass);
		NewAbility->AbilityComponent = this;
		ActiveAbilities.Add(NewAbility);
	}
}

void UAbilityComponent::BindAllValueDelegatesAndInit()
{
	if (WeaponAbility == nullptr)
	{
		return;
	}
	//需要UI显示的就在这里绑定，不需要的就直接用函数返回
	//1. 绑定
	WeaponAbility->OnMaxMagChanged.AddLambda([this](FName AbilityName, float NewValue)-> void
	{
		SurvivalPlayerCharacter->MaxMagCount = NewValue;
		SurvivalPlayerCharacter->OnRep_MaxMagCount();
	});

	//2. 获取值并广播
	WeaponAbility->UpdateValues();
	for (auto Ability : ActiveAbilities)
	{
		Ability->UpdateValues();
	}
}
