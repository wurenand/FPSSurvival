#include "Components/AbilityComponent.h"

#include "Ability/WeaponAbility.h"
#include "Character/SurvivalPlayerCharacter.h"
#include "Library/DataHelperLibrary.h"
#include "Net/UnrealNetwork.h"

UAbilityComponent::UAbilityComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UAbilityComponent::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(UAbilityComponent, WeaponAbility);
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
		WeaponAbility->AddLevel();
	}
	else
	{
		for (AAbilityBase* Ability : ActiveAbilities)
		{
			if (Ability->GetAbilityName() == AbilityName)
			{
				Ability->AddLevel();
				return;
			}
		}
		//没有这个技能
		GiveAbility(AbilityName);
	}
}

AAbilityBase* UAbilityComponent::GiveAbility(FName AbilityName)
{
	FActorSpawnParameters SpawnParameters;
	SpawnParameters.Owner = GetOwner();
	AAbilityBase* NewAbility = nullptr;
	if (AbilityName == TEXT("Weapon"))
	{
		WeaponAbility = GetWorld()->SpawnActor<AWeaponAbility>(SpawnParameters);
		NewAbility = WeaponAbility;
	}
	else
	{
		FAbilityDataTableRow AbilityInfo = UDataHelperLibrary::GetAbilityDataFromName(GetWorld(), AbilityName);
		if (AbilityInfo.AbilityClass)
		{
			NewAbility = GetWorld()->SpawnActor<AAbilityBase>(AbilityInfo.AbilityClass, SpawnParameters);
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("%s : Ability Class not found"), *AbilityName.ToString());
		}
	}
	NewAbility->AbilityComponent = this;
	//初始化数值
	NewAbility->UpdateValues();
	return NewAbility;
}


void UAbilityComponent::BindAllValueDelegatesAndInit()
{
	if (WeaponAbility == nullptr)
	{
		//说明AC第一次使用，GiveWeaponAbility
		GiveAbility(TEXT("Weapon"));
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
