// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Ability/GA/GameplayAbilityBase.h"
#include "GA_EffectOnly.generated.h"

/**
 * 自身的纯数据GA 激活时会ApplyGE更新Attribute
 */
UCLASS()
class SURVIVAL_API UGA_EffectOnly : public UGameplayAbilityBase
{
	GENERATED_BODY()
public:
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;	
};
