// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "AttributeSet.h"
#include "SurvivalAttributeSet.generated.h"

//创建Attribute使用的辅助宏
#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)


/**
 * 
 */
UCLASS()
class SURVIVAL_API USurvivalAttributeSet : public UAttributeSet
{
	GENERATED_BODY()

public:
	USurvivalAttributeSet();

	//重写重要函数
	//在对CurrentValue的修改之前会调用  只会改变Modifier的结果，不对Modifier做改变
	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;
	//在BaseValue修改之后会被调用  完成这个函数之后，值才会被同步到Client
	virtual void PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data) override;

	virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;

	UPROPERTY(BlueprintReadOnly, Category="Attribute|Health", ReplicatedUsing=OnRep_Health)
	FGameplayAttributeData Health;
	ATTRIBUTE_ACCESSORS(USurvivalAttributeSet, Health)

	UPROPERTY(BlueprintReadOnly, Category="Attribute|MaxHealth", ReplicatedUsing=OnRep_MaxHealth)
	FGameplayAttributeData MaxHealth;
	ATTRIBUTE_ACCESSORS(USurvivalAttributeSet, MaxHealth)

	UPROPERTY(BlueprintReadOnly, Category="Attribute|MagCount", ReplicatedUsing=OnRep_MagCount)
	FGameplayAttributeData MagCount;
	ATTRIBUTE_ACCESSORS(USurvivalAttributeSet, MagCount)

	UPROPERTY(BlueprintReadOnly, Category="Attribute|MaxMagCount", ReplicatedUsing=OnRep_MaxMagCount)
	FGameplayAttributeData MaxMagCount;
	ATTRIBUTE_ACCESSORS(USurvivalAttributeSet, MaxMagCount)

protected:
	UFUNCTION()
	void OnRep_Health(const FGameplayAttributeData& OldValue);
	UFUNCTION()
	void OnRep_MaxHealth(const FGameplayAttributeData& OldValue);
	UFUNCTION()
	void OnRep_MagCount(const FGameplayAttributeData& OldValue);
	UFUNCTION()
	void OnRep_MaxMagCount(const FGameplayAttributeData& OldValue);
};
