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

	void AddXP(int32 XPToAdd);
protected:
	UPROPERTY(ReplicatedUsing = OnRep_XP)
	int32 XP = 0;
	UFUNCTION()
	void OnRep_XP();
	UPROPERTY(Replicated)
	int32 Level = 1;
};
