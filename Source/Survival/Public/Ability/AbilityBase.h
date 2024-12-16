// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "AbilityBase.generated.h"

class UAbilityBase;
class ASurvivalPlayerCharacter;
class UAbilityComponent;
DECLARE_MULTICAST_DELEGATE_TwoParams(FOnAbilityValueChangedSignature, FName AbilityName, float NewValue);

//用来读取表中属性值的辅助宏
#define GET_VALUE_FROM_CURVE_HELPER(AttributeName,Level) \
if (DataTableRow.AbilityCurveTable) \
{ \
FString ContextString; \
FString BaseCurveName = FString::Printf(TEXT("Base%hs"), #AttributeName); \
FString CurveMultName = FString::Printf(TEXT("%hsMult"), #AttributeName); \
FRealCurve* BaseCurve = DataTableRow.AbilityCurveTable->FindCurve(*BaseCurveName, ContextString); \
FRealCurve* CurveMult = DataTableRow.AbilityCurveTable->FindCurve(*CurveMultName, ContextString); \
Base##AttributeName = BaseCurve ? BaseCurve->Eval(Level) : 0; \
AttributeName##Mult = CurveMult ? CurveMult->Eval(Level) : 0; \
}


/**
 * Ability同步给其他人的结构体，Ability只在Server出现
 */
USTRUCT(BlueprintType)
struct FAbilityHandle
{
	GENERATED_BODY()
	UPROPERTY(BlueprintReadOnly, Category="Ability")
	FName AbilityName;
	UPROPERTY(BlueprintReadOnly, Category="Ability")
	int32 Level = 1;
};

USTRUCT(BlueprintType)
struct FAbilityDataTableRow : public FTableRowBase
{
	GENERATED_BODY()
	//Ability的各级数据表
	UPROPERTY(EditAnywhere, Category = "AbilityData")
	TObjectPtr<UCurveTable> AbilityCurveTable;
	//数据表中每个Curve属性的Name对应的显示名字
	UPROPERTY(EditAnywhere, Category = "AbilityData")
	TMap<FName, FName> CurveNameToDisplayName;
	//Ability的类型
	UPROPERTY(EditAnywhere, Category = "AbilityData")
	TSubclassOf<UAbilityBase> AbilityClass;
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
 * 其他属性在Server端做修改，而发生变化时，会改动Character中对应的变量，那个会做同步 以后可以改掉
 */
UCLASS(Blueprintable)
class SURVIVAL_API UAbilityBase : public UObject
{
	GENERATED_BODY()

public:
	MAKE_PUBLIC_VALUE_FUNCTIONS(BaseGeneral, GeneralMult)
	MAKE_PUBLIC_VALUE_FUNCTIONS(BaseDamage, DamageMult)
	MAKE_PUBLIC_VALUE_FUNCTIONS(BaseFrequency, FrequencyMult)

	FORCEINLINE int32 GetLevel() const { return Level; }
	FOnAbilityValueChangedSignature OnGeneralValueChanged; //广播最终结果 Base * Mult

	void AddLevel();
	//会根据当前Level来读取值 并且广播 第一次Give和AddLevel都会调用
	virtual void UpdateValues();

	TObjectPtr<UAbilityComponent> AbilityComponent;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Ability")
	FName AbilityName;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Ability")
	int32 Level = 1;

	FAbilityDataTableRow DataTableRow;

	//通用数据，例如HP，移速等。避免创建新的子类
	MAKE_VALUE(General)
	MAKE_VALUE(Damage) //伤害
	MAKE_VALUE(Frequency) //攻击速度/频率
};
