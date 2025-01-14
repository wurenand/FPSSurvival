// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Interface/CombatInterface.h"
#include "Survival/Survival.h"
#include "SurvivalCharacterBase.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnCharacterValueChangedSignature,float,NewValue);

UCLASS()
class SURVIVAL_API ASurvivalCharacterBase : public ACharacter, public ICombatInterface
{
	GENERATED_BODY()

public:
	ASurvivalCharacterBase();

	virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;
	//TODO:用于初始化数值的，包括HP，弹药等 Player与Enemy不同
	virtual void InitializeAttributes();

	//~Begin ICombatInterface
	//交给子类来实现
	virtual ETeam GetCharacterTeam() override;
	virtual void CombatTakeDamage(ASurvivalCharacterBase* DamageInstigator, float DamageValue) override;
	//~End ICombatInterface

	//~Begin Death
	//只在Server上调用，用于处理Character死后的逻辑，例如Weapon的Destroy bQuickDestroy == true直接Destroy
	virtual void SetPendingDeath(bool bQuickDestroy = false);
	//多播 播放蒙太奇等 死亡相关动画特效 以及设置 例如关闭碰撞
	UFUNCTION(NetMulticast,Reliable)
	virtual void Mult_DeathEffect();
	//~End Death

	UPROPERTY(BlueprintAssignable)
	FOnCharacterValueChangedSignature OnHPChanged;
	UPROPERTY(BlueprintAssignable)
	FOnCharacterValueChangedSignature OnMaxHPChanged;
	
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, ReplicatedUsing = OnRep_MaxHealth, Category="Health")
	float MaxHealth = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, ReplicatedUsing = OnRep_Health, Category="Health")
	float Health = 0;
	UFUNCTION()
	void OnRep_MaxHealth();
	UFUNCTION()
	void OnRep_Health();

	//Enemy默认就是NoTeam不需要修改，Player的会从PlayerState获取更新
	ETeam Team = ETeam::ETeam_NoTeam;
};
