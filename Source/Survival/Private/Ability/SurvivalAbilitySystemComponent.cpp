#include "Ability/SurvivalAbilitySystemComponent.h"
#include "GameplayTagsManager.h"
#include "Ability/GA/GameplayAbilityBase.h"

USurvivalAbilitySystemComponent::USurvivalAbilitySystemComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void USurvivalAbilitySystemComponent::TryActivateAbilityByTag(const FGameplayTag& Tag)
{
	if (!Tag.IsValid())
	{
		return;
	}
	FGameplayTag AbilityTag = Tag;
	if (Tag.MatchesTag(UGameplayTagsManager::Get().RequestGameplayTag(FName("InputTag"))))
	{
		if (FGameplayTag* Value = InputTagToAbility.Find(Tag))
		{
			AbilityTag = *Value;
		}
	}
	for (FGameplayAbilitySpec& ActivateAbility : GetActivatableAbilities())
	{
		if (ActivateAbility.DynamicAbilityTags.HasTagExact(AbilityTag))
		{
			TryActivateAbility(ActivateAbility.Handle);
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
}
