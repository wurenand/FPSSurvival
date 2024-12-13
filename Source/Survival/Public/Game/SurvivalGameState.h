// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

 #include "CoreMinimal.h"
#include "TotalGameStateBase.h"
#include "SurvivalGameState.generated.h"

/**
 * 
 */
UCLASS()
class SURVIVAL_API ASurvivalGameState : public ATotalGameStateBase
{
	GENERATED_BODY()

public:
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	//Callable Test
	UFUNCTION(BlueprintCallable, Category = "Survival")
	void AddXP(int32 XPToAdd);
	void SetAllGamePause(bool Pause);
	
	UPROPERTY(BlueprintAssignable)
	FOnGameStateValueChangedSignature OnXPPercentChanged;
	UPROPERTY(BlueprintAssignable)
	FOnGameStateValueChangedSignature OnLevelChanged;
protected:
	UPROPERTY(ReplicatedUsing = OnRep_XP)
	int32 XP = 0;
	UFUNCTION()
	void OnRep_XP();
	UPROPERTY(ReplicatedUsing = OnRep_Level)
	int32 Level = 1;
	UFUNCTION()
	void OnRep_Level();

	UPROPERTY(ReplicatedUsing = OnRep_bIsPaused)
	bool bIsPaused = false;
	UFUNCTION()
	void OnRep_bIsPaused();
};