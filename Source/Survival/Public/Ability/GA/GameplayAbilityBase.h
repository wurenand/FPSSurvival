// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "GameplayAbilityBase.generated.h"

/**
 * 所有Ability的基类
 */
UCLASS()
class SURVIVAL_API UGameplayAbilityBase : public UGameplayAbility
{
	GENERATED_BODY()

public:
	//主动触发的按键，如果有的话
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Ability")
	FGameplayTag InputTrigger;
	//标识区分当前是哪个Ability
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category="Ability")
	FGameplayTag AbilityTag;
	//是否自动触发，可以用于被动技能
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Ability")
	bool bAutoActivateOnGranted = false;
	//TODO: ? 什么被动技能

protected:
	//伤害数值
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Ability|Values")
	FScalableFloat Damage;
	//造成伤害的GE类
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category="Ability")
	TSubclassOf<UGameplayEffect> DamageEffectClass;
};
