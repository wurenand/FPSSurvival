// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "AbilityBase.generated.h"

class ASurvivalPlayerCharacter;
class AAbilityBase;
class UAbilityComponent;
DECLARE_MULTICAST_DELEGATE_TwoParams(FOnAbilityValueChangedSignature, FName AbilityName, float NewValue);

USTRUCT(BlueprintType)
struct FAbilityDataTableRow : public FTableRowBase
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, Category = "AbilityData")
	TObjectPtr<UCurveTable> AbilityCurveTable;
	UPROPERTY(EditAnywhere, Category = "AbilityData")
	TSubclassOf<AAbilityBase> AbilityClass;
	UPROPERTY(EditAnywhere, Category = "AbilityData")
	FName AbilityName;
	UPROPERTY(EditAnywhere, Category = "AbilityData")
	UTexture2D* AbilityIcon;
};

//辅助生成Public函数开放给需要使用的地方
#define MAKE_PUBLIC_VALUE_FUNCTIONS(BaseValue, ValueMult) \
FORCEINLINE float Get##BaseValue() const { return BaseValue; } \
FORCEINLINE float Get##ValueMult() const { return ValueMult; }
//创建新变量的宏
#define MAKE_VALUE(ValueName)\
UPROPERTY(VisibleAnywhere, Category = "Values")\
float Base##ValueName = 1.0f;\
UPROPERTY(VisibleAnywhere, Category = "Values")\
float ValueName##Mult = 1.0f;

/**
 * 修改为AActor的子类，使用网络复制功能
 * 同步一下Level其实就够
 * 其他属性在Server端做修改，而发生变化时，会改动Character中对应的变量，那个会做同步 以后可以改掉
 */
UCLASS()
class SURVIVAL_API AAbilityBase : public AActor
{
	GENERATED_BODY()

public:
	AAbilityBase();
	MAKE_PUBLIC_VALUE_FUNCTIONS(BaseGeneral,GeneralMult)
	MAKE_PUBLIC_VALUE_FUNCTIONS(BaseDamage,DamageMult)
	MAKE_PUBLIC_VALUE_FUNCTIONS(BaseFrequency,FrequencyMult)
	
	virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;

	FOnAbilityValueChangedSignature OnGeneralValueChanged;//广播最终结果 Base * Mult
	
	void AddLevel();
	//会根据当前Level来读取值 并且广播
	virtual void UpdateValues();

	TObjectPtr<UAbilityComponent> AbilityComponent;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Ability")
	FName AbilityName;
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, ReplicatedUsing = OnRep_Level, Category="Ability")
	int32 Level = 1;
	UFUNCTION()
	void OnRep_Level();

	FAbilityDataTableRow DataTableRow;

	//通用数据，例如HP，移速等。避免创建新的子类
	MAKE_VALUE(General)
	MAKE_VALUE(Damage)//伤害
	MAKE_VALUE(Frequency)//攻击速度/频率
};
