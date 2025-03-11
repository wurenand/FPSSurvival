// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayAbilityBase.h"
#include "GA_Reload.generated.h"

/**
 * 
 */
UCLASS()
class SURVIVAL_API UGA_Reload : public UGameplayAbilityBase
{
	GENERATED_BODY()
public:
	UGA_Reload();
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;

protected:
	UFUNCTION()
	void OnMontageCompleted();
	UFUNCTION()
	void OnEventReceived(FGameplayEventData PayLoad);
};
