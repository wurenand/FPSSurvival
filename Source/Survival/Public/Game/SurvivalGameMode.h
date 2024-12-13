// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TotalGameModeBase.h"
#include "SurvivalGameMode.generated.h"

class ASurvivalGameState;
/**
 * 
 */
UCLASS()
class SURVIVAL_API ASurvivalGameMode : public ATotalGameModeBase
{
	GENERATED_BODY()

public:
	virtual void PlayerEliminated(ASurvivalCharacterBase* EliminatedCharacter,
	                              ASurvivalPlayerController* VictimController,
	                              ASurvivalPlayerController* AttackerController) override;

	void EnemyEliminated(ASurvivalCharacterBase* EliminatedCharacter, ASurvivalPlayerController* AttackerController);
	void LevelUp();
	void PlayerResume(ASurvivalPlayerController* Player);
protected:
	ASurvivalGameState* GetSurvivalGameState();
	TObjectPtr<ASurvivalGameState> SurvivalGameState;
	//记录选择完成的所有玩家
	TArray<ASurvivalPlayerController*> ReadyPlayers;
};
