// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"

#include "SurvivalAbilitySystemComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class SURVIVAL_API USurvivalAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()

public:
	USurvivalAbilitySystemComponent();
	//激活技能接口 同时使用InputTag和AbilityTag
	void TryActivateAbilityByTag(const FGameplayTag& Tag);
	void TryGiveAbility(const FGameplayAbilitySpec& Spec);

protected:
	//记录已给予技能的InputTagToAbilityTag
	TMap<FGameplayTag,FGameplayTag> InputTagToAbility;
};
