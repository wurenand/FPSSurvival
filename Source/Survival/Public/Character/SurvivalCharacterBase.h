// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Interface/CombatInterface.h"
#include "Survival/Survival.h"
#include "SurvivalCharacterBase.generated.h"

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
	//~End ICombatInterface
	
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, ReplicatedUsing = OnRep_MaxHealth, Category="Health")
	float MaxHealth;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, ReplicatedUsing = OnRep_Health, Category="Health")
	float Health;
	UFUNCTION()
	void OnRep_MaxHealth();
	UFUNCTION()
	void OnRep_Health();

	//Enemy默认就是NoTeam不需要修改，Player的会从PlayerState获取更新
	ETeam Team = ETeam::ETeam_NoTeam;
};
