#include "Components/AbilityComponent.h"

#include "Ability/WeaponAbility.h"
#include "Character/SurvivalPlayerCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "Library/DataHelperLibrary.h"
#include "Net/UnrealNetwork.h"

UAbilityComponent::UAbilityComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UAbilityComponent::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(UAbilityComponent, AbilityHandles)
}

const FAbilityHandle* UAbilityComponent::IsOwningAbility(FName AbilityName) const
{
	for (auto& Handle : AbilityHandles)
	{
		if (Handle.AbilityName == AbilityName)
		{
			return &Handle;
		}
	}
	return nullptr;
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
	UAbilityBase* Ability = nullptr;
	if (AbilityName == TEXT("Weapon"))
	{
		WeaponAbility->AddLevel();
		Ability = WeaponAbility;
	}
	else
	{
		if (NameToAbility.Find(AbilityName) == nullptr)
		{
			//没有这个技能
			GiveAbility(AbilityName);
			return;
		}
		NameToAbility[AbilityName]->AddLevel();
		Ability = NameToAbility[AbilityName];
	}
	//同步升级后的新等级
	for (FAbilityHandle& Handle : AbilityHandles)
	{
		if (Handle.AbilityName == AbilityName)
		{
			Handle.Level = Ability->GetLevel();
			OnRep_AbilityHandles();
			return;
		}
	}
}

UAbilityBase* UAbilityComponent::GiveAbility(FName AbilityName)
{
	UAbilityBase* NewAbility = nullptr;
	if (AbilityName == TEXT("Weapon"))
	{
		WeaponAbility = NewObject<UWeaponAbility>();
		NewAbility = WeaponAbility;
	}
	else
	{
		FAbilityDataTableRow AbilityInfo = UDataHelperLibrary::GetAbilityDataFromName(GetWorld(), AbilityName);
		if (AbilityInfo.AbilityClass)
		{
			NewAbility = NewObject<UAbilityBase>(AbilityInfo.AbilityClass);
			//Add
			ActiveAbilities.Add(NewAbility);
			NameToAbility.Emplace(AbilityName, NewAbility);
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("%s : Ability Class not found"), *AbilityName.ToString());
		}
	}
	NewAbility->AbilityName = AbilityName;
	NewAbility->AbilityComponent = this;
	//同步
	AbilityHandles.Emplace(AbilityName, 1);
	OnRep_AbilityHandles();
	//初始化数值
	NewAbility->UpdateValues();
	return NewAbility;
}

void UAbilityComponent::BindAllValueDelegatesAndInit()
{
	//WeaponAbility
	if (WeaponAbility == nullptr)
	{
		//说明AC第一次使用，GiveWeaponAbility
		GiveAbility(TEXT("Weapon"));
	}
	//Health Ability
	if (NameToAbility.Find(TEXT("Health")) == nullptr)
	{
		GiveAbility(TEXT("Health"));
	}
	//需要UI显示的就在这里绑定，不需要的就直接用函数返回
	//1. 绑定
	//Weapon
	WeaponAbility->OnMaxMagChanged.AddLambda([this](FName AbilityName, float NewValue)-> void
	{
		SurvivalPlayerCharacter->MaxMagCount = NewValue; //修改Replicated的值
		SurvivalPlayerCharacter->OnRep_MaxMagCount(); //为Server广播
	});
	//Health
	NameToAbility[TEXT("Health")]->OnGeneralValueChanged.AddLambda([this](FName AbilityName, float NewValue)-> void
	{
		float Offset = NewValue - SurvivalPlayerCharacter->MaxHealth;
		SurvivalPlayerCharacter->MaxHealth = NewValue;
		SurvivalPlayerCharacter->Health += Offset;
		SurvivalPlayerCharacter->OnRep_Health();
		SurvivalPlayerCharacter->OnRep_MaxHealth();
	});

	//2. 获取值并广播
	WeaponAbility->UpdateValues();
	for (auto Ability : ActiveAbilities)
	{
		Ability->UpdateValues();
	}
}

void UAbilityComponent::OnRep_AbilityHandles()
{
	for (auto& Handle : AbilityHandles)
	{
		UKismetSystemLibrary::PrintString(
			this, ("Ability" + Handle.AbilityName.ToString() + "Level : " + FString::FromInt(Handle.Level)));
	}
}
