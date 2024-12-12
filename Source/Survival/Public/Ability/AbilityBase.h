// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "AbilityBase.generated.h"

class UAbilityComponent;
DECLARE_MULTICAST_DELEGATE_TwoParams(FOnAbilityValueChangedSignature, FName AbilityName, float NewValue);

USTRUCT(BlueprintType)
struct FAbilityDataTableRow : public FTableRowBase
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, Category = "AbilityData")
	TObjectPtr<UCurveTable> AbilityCurveTable;
};

/**
 * 目前值都是不同步的，如果需要同步(例如Client需要某些数据来播放特效等。
 * 可以1.通过绑定委托到Character上的同步变量
 *    2.让这个UObject支持同步 IsSupportedForNet，这样可以让UObject的属性也支持同步)
 */
UCLASS()
class SURVIVAL_API UAbilityBase : public UObject
{
	GENERATED_BODY()
public:
	FORCEINLINE float GetBaseDamage() const{return BaseDamage;}
	FORCEINLINE float GetDamageMult() const{return DamageMult;}
	FORCEINLINE float GetBaseFrequency() const{return BaseFrequency;}
	FORCEINLINE float GetFrequencyMult() const{return FrequencyMult;}
	
	void AddLevel();
	
	//会根据当前Level来读取值 并且广播
	virtual void UpdateValues();

	TObjectPtr<UAbilityComponent> AbilityComponent;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Ability")
	FName AbilityName;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Ability")
	int32 Level = 1;

	FAbilityDataTableRow DataTableRow;
	
	UPROPERTY(VisibleAnywhere, Category = "Values")
	float BaseDamage = 1.0f;//基础伤害
	UPROPERTY(VisibleAnywhere, Category = "Values")
	float DamageMult = 1.0f;//伤害倍率
	UPROPERTY(VisibleAnywhere, Category = "Values")
	float BaseFrequency = 1.0f;//攻击速度
	UPROPERTY(VisibleAnywhere, Category = "Values")
	float FrequencyMult = 1.0f;
};
