// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TotalGameStateBase.h"
#include "CounterStrikeGameState.generated.h"

/**
 * 
 */
UCLASS()
class SURVIVAL_API ACounterStrikeGameState : public ATotalGameStateBase
{
	GENERATED_BODY()

public:
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	void UpdatePlayerTeam(ASurvivalPlayerState* Player);
	
	UPROPERTY(BlueprintAssignable,Category = "Info")
	FOnGameStateValueChangedSignature OnRedTeamCountChangedDelegate;
	UPROPERTY(BlueprintAssignable,Category = "Info")
	FOnGameStateValueChangedSignature OnBlueTeamCountChangedDelegate;

protected:
	UPROPERTY(ReplicatedUsing = OnRep_RedPlayers)
	TArray<ASurvivalPlayerState*> RedPlayers;
	UFUNCTION()
	void OnRep_RedPlayers();
	UPROPERTY(ReplicatedUsing = OnRep_BluePlayers)
	TArray<ASurvivalPlayerState*> BluePlayers;
	UFUNCTION()
	void OnRep_BluePlayers();
};
