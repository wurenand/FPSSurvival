// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "AbilityBase.generated.h"

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
};

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
	FORCEINLINE float GetBaseDamage() const { return BaseDamage; }
	FORCEINLINE float GetDamageMult() const { return DamageMult; }
	FORCEINLINE float GetBaseFrequency() const { return BaseFrequency; }
	FORCEINLINE float GetFrequencyMult() const { return FrequencyMult; }
	
	FORCEINLINE const FName& GetAbilityName() const { return AbilityName; }

	virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;

	void AddLevel();

	//会根据当前Level来读取值 并且广播
	virtual void UpdateValues();

	TObjectPtr<UAbilityComponent> AbilityComponent;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Ability")
	FName AbilityName;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, ReplicatedUsing = OnRep_Level, Category="Ability")
	int32 Level = 1;
	UFUNCTION()
	void OnRep_Level();

	FAbilityDataTableRow DataTableRow;

	UPROPERTY(VisibleAnywhere, Category = "Values")
	float BaseDamage = 1.0f; //基础伤害
	UPROPERTY(VisibleAnywhere, Category = "Values")
	float DamageMult = 1.0f; //伤害倍率
	UPROPERTY(VisibleAnywhere, Category = "Values")
	float BaseFrequency = 1.0f; //攻击速度
	UPROPERTY(VisibleAnywhere, Category = "Values")
	float FrequencyMult = 1.0f;
};
