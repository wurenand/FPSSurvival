// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TotalGameStateBase.h"
#include "CounterStrikeGameState.generated.h"

class ASurvivalPlayerController;
/**
 * 
 */
UCLASS()
class SURVIVAL_API ACounterStrikeGameState : public ATotalGameStateBase
{
	GENERATED_BODY()

public:
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	//PS调用
	void UpdatePlayerTeam(ASurvivalPlayerState* Player);


	/**
	 * 由GM调用，当角色死亡时调用 处理当前一轮结束的相关逻辑
	 * @param DeadPC 传入死亡的PlayerController
	 * @return 此轮游戏是否已经结束 若为true，GM需要负责Respawn所有玩家
	 */
	bool IsRoundOver(ASurvivalPlayerController* DeadPC);

	UPROPERTY(BlueprintAssignable, Category = "Info")
	FOnGameStateValueChangedSignature OnRedTeamCountChangedDelegate;
	UPROPERTY(BlueprintAssignable, Category = "Info")
	FOnGameStateValueChangedSignature OnBlueTeamCountChangedDelegate;
	UPROPERTY(BlueprintAssignable, Category = "Info")
	FOnGameStateValueChangedSignature OnRedScoreChangedDelegate;
	UPROPERTY(BlueprintAssignable, Category = "Info")
	FOnGameStateValueChangedSignature OnBlueScoreChangedDelegate;

	UPROPERTY(ReplicatedUsing = OnRep_RedScore)
	int32 RedScore = 0;
	UFUNCTION()
	void OnRep_RedScore();
	UPROPERTY(ReplicatedUsing = OnRep_BlueScore)
	int32 BlueScore = 0;
	UFUNCTION()
	void OnRep_BlueScore();
	
	//RedPlayers记录当前阵营的所有人，不管存活与否 RedDeadPlayers只记录已经死亡的
	UPROPERTY(ReplicatedUsing = OnRep_RedPlayers)
	TArray<ASurvivalPlayerState*> RedPlayers;
	UFUNCTION()
	void OnRep_RedPlayers();
	UPROPERTY(ReplicatedUsing = OnRep_RedDeadPlayers)
	TArray<ASurvivalPlayerState*> RedDeadPlayers;
	UFUNCTION()
	void OnRep_RedDeadPlayers();
	UPROPERTY(ReplicatedUsing = OnRep_BluePlayers)
	TArray<ASurvivalPlayerState*> BluePlayers;
	UFUNCTION()
	void OnRep_BluePlayers();
	UPROPERTY(ReplicatedUsing = OnRep_BlueDeadPlayers)
	TArray<ASurvivalPlayerState*> BlueDeadPlayers;
	UFUNCTION()
	void OnRep_BlueDeadPlayers();
};
