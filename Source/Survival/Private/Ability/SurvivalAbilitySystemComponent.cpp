#include "Ability/SurvivalAbilitySystemComponent.h"
#include "GameplayTagsManager.h"
#include "Ability/GA/GameplayAbilityBase.h"

USurvivalAbilitySystemComponent::USurvivalAbilitySystemComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void USurvivalAbilitySystemComponent::TryActivateAbilityByTag(const FGameplayTag& Tag)
{
	UE_LOG(LogActor, Warning, TEXT("------------Begin------------ InputTag : %s"), *Tag.GetTagName().ToString())
	if (!Tag.IsValid())
	{
		return;
	}
	FGameplayTag AbilityTag = Tag;
	if (Tag.MatchesTag(UGameplayTagsManager::Get().RequestGameplayTag(FName("Input"))))
	{
		if (FGameplayTag* Value = InputTagToAbility.Find(Tag))
		{
			AbilityTag = *Value;
		}
	}
	UE_LOG(LogActor, Warning, TEXT("AbilityTag : %s"), *AbilityTag.GetTagName().ToString())
	for (FGameplayAbilitySpec& ActivateAbility : GetActivatableAbilities())
	{
		UE_LOG(LogActor, Warning, TEXT("CurrentAbility : %s"), *ActivateAbility.Ability.GetName())
		if (ActivateAbility.Ability->AbilityTags.HasTagExact(AbilityTag))
		{
			TryActivateAbility(ActivateAbility.Handle);
			UE_LOG(LogActor, Warning, TEXT("AbilityTryActivate"))
		}
	}
}

void USurvivalAbilitySystemComponent::TryGiveAbility(const FGameplayAbilitySpec& Spec)
{
	GiveAbility(Spec);
	if (UGameplayAbilityBase* Ability = Cast<UGameplayAbilityBase>(Spec.Ability))
	{
		InputTagToAbility.Emplace(Ability->InputTrigger, Ability->AbilityTags.GetByIndex(0));
	}

	//处理授予即触发的逻辑
	if (UGameplayAbilityBase* AbilityBase = Cast<UGameplayAbilityBase>(Spec.Ability))
	{
		if (AbilityBase->bAutoActivateOnGranted)
		{
			TryActivateAbilityByTag(AbilityBase->AbilityTags.GetByIndex(0));
		}
	}
}
