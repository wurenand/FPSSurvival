// Fill out your copyright notice in the Description page of Project Settings.


#include "Ability/GA/GA_EffectOnly.h"

#include "Character/SurvivalCharacterBase.h"


void UGA_EffectOnly::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
                                     const FGameplayAbilityActorInfo* ActorInfo,
                                     const FGameplayAbilityActivationInfo ActivationInfo,
                                     const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
	if (ASurvivalCharacterBase* CharacterBase = Cast<ASurvivalCharacterBase>(ActorInfo->AvatarActor))
	{
		CharacterBase->ApplyGameplayEffectToSelf(EffectClass, GetAbilityLevel());
	}
}
