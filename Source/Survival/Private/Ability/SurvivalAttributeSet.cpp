// Fill out your copyright notice in the Description page of Project Settings.


#include "Ability/SurvivalAttributeSet.h"

#include "Net/UnrealNetwork.h"

void USurvivalAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	Super::PreAttributeChange(Attribute, NewValue);
}

void USurvivalAttributeSet::PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);
}

void USurvivalAttributeSet::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	//这里强制Rep，即使属性没有变化也会同步，为了保证预测功能
	DOREPLIFETIME_CONDITION_NOTIFY(USurvivalAttributeSet, Health, COND_None, REPNOTIFY_Always)
	DOREPLIFETIME_CONDITION_NOTIFY(USurvivalAttributeSet, MaxHealth, COND_None, REPNOTIFY_Always)
	DOREPLIFETIME_CONDITION_NOTIFY(USurvivalAttributeSet, MagCount, COND_None, REPNOTIFY_Always)
	DOREPLIFETIME_CONDITION_NOTIFY(USurvivalAttributeSet, MaxMagCount, COND_None, REPNOTIFY_Always)
}

void USurvivalAttributeSet::OnRep_Health(const FGameplayAttributeData& OldValue)
{
	//通知预测系统数据被同步了
	GAMEPLAYATTRIBUTE_REPNOTIFY(USurvivalAttributeSet, Health, OldValue)
}

void USurvivalAttributeSet::OnRep_MaxHealth(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(USurvivalAttributeSet, MaxHealth, OldValue)
}

void USurvivalAttributeSet::OnRep_MagCount(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(USurvivalAttributeSet, MagCount, OldValue)
}

void USurvivalAttributeSet::OnRep_MaxMagCount(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(USurvivalAttributeSet, MaxMagCount, OldValue)
}
