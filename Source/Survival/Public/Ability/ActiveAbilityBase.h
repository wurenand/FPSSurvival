// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Ability/AbilityBase.h"
#include "ActiveAbilityBase.generated.h"

class AProjectileBase;
/**
 * 非纯数据Ability，需要数据中包含Frequency，作为Timer触发的时间频率
 */
UCLASS()
class SURVIVAL_API UActiveAbilityBase : public UAbilityBase
{
	GENERATED_BODY()
	
public:
	virtual void UpdateValues() override;

protected:
	//每次实际触发的事件
	virtual void TriggerActiveEvent();
	FTimerHandle ActiveTimerHandle;

	UPROPERTY(EditAnywhere,Category = "AbilitySpawnActor")
	TSubclassOf<AProjectileBase> ProjectileClass;
};
