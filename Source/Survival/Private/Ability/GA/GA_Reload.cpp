// Fill out your copyright notice in the Description page of Project Settings.


#include "Ability/GA/GA_Reload.h"

#include "Abilities/Tasks/AbilityTask_PlayMontageAndWait.h"
#include "Abilities/Tasks/AbilityTask_WaitGameplayEvent.h"
#include "Character/SurvivalCharacterBase.h"

UGA_Reload::UGA_Reload()
{
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
}

void UGA_Reload::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
                                 const FGameplayAbilityActivationInfo ActivationInfo,
                                 const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
	UAbilityTask_PlayMontageAndWait* MontageProxy = UAbilityTask_PlayMontageAndWait::CreatePlayMontageAndWaitProxy(
		this, NAME_None, MontageToPlay, 1);
	UAbilityTask_WaitGameplayEvent* Event = UAbilityTask_WaitGameplayEvent::WaitGameplayEvent(
		this, FGameplayTag::RequestGameplayTag(FName("Event.Reload")));
	MontageProxy->OnCompleted.AddDynamic(this, &UGA_Reload::OnMontageCompleted);
	Event->EventReceived.AddDynamic(this, &UGA_Reload::OnEventReceived);
	Event->Activate();
	MontageProxy->Activate();
}

void UGA_Reload::OnMontageCompleted()
{
	EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, false);
}

void UGA_Reload::OnEventReceived(FGameplayEventData PayLoad)
{
	if (PayLoad.EventTag != FGameplayTag::RequestGameplayTag(FName("Event.Reload")))
	{
		return;
	}
	if (ASurvivalCharacterBase* CharacterBase = Cast<ASurvivalCharacterBase>(CurrentActorInfo->AvatarActor))
	{
		//回复子弹
		CharacterBase->ApplyGameplayEffectToSelf(EffectClass, 1);
	}
}
