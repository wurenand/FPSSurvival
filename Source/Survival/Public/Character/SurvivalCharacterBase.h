// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Interface/CombatInterface.h"
#include "Survival/Survival.h"
#include "SurvivalCharacterBase.generated.h"

struct FGameplayTag;
class UGameplayEffect;
class UGameplayAbilityBase;
class USurvivalAbilitySystemComponent;
class USurvivalAttributeSet;
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnCharacterValueChangedSignature, float, NewValue);

UCLASS()
class SURVIVAL_API ASurvivalCharacterBase : public ACharacter, public ICombatInterface
{
	GENERATED_BODY()

public:
	ASurvivalCharacterBase();

	virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;

	//得到AbilityComponent后的初始化  负责Weapon，HUD Params，AbilityComponent的初始化
	virtual void InitializeCharacter();

	//授予ASC能力的接口
	virtual void GiveCharacterAbility(TSubclassOf<UGameplayAbilityBase> AbilityClass, int32 Level);
	//给自身施加GE的接口
	void ApplyGameplayEffectToSelf(const TSubclassOf<UGameplayEffect>& EffectToBeApplied, float Level);

	//~Begin ICombatInterface
	//交给子类来实现
	virtual ETeam GetCharacterTeam() override;
	virtual void CombatTakeDamage(ASurvivalCharacterBase* DamageInstigator, float DamageValue) override;
	//~End ICombatInterface

	//~Begin Death
	//只在Server上调用，用于处理Character死后的逻辑，例如Weapon的Destroy bQuickDestroy == true直接Destroy
	virtual void SetPendingDeath(bool bQuickDestroy = false);
	//多播 播放蒙太奇等 死亡相关动画特效 以及设置 例如关闭碰撞
	UFUNCTION(NetMulticast, Reliable)
	virtual void Mult_DeathEffect();
	//~End Death

	UPROPERTY(BlueprintAssignable)
	FOnCharacterValueChangedSignature OnHPChanged;
	UPROPERTY(BlueprintAssignable)
	FOnCharacterValueChangedSignature OnMaxHPChanged;

protected:
	TObjectPtr<USurvivalAbilitySystemComponent> AbilitySystemComponent;
	TObjectPtr<USurvivalAttributeSet> AttributeSet;

	//初始化自带GA
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category="Ability")
	TArray<TSubclassOf<UGameplayAbilityBase>> StartupAbilityClasses;
	//Spawn或ReSpawn时用来恢复HP等数据到默认值的
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category="Ability")
	TArray<TSubclassOf<UGameplayEffect>> DefaultEffectClasses;

	//Enemy默认就是NoTeam不需要修改，Player的会从PlayerState获取更新
	ETeam Team = ETeam::ETeam_NoTeam;
};
