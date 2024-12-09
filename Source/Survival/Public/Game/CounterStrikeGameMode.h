// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TotalGameModeBase.h"
#include "CounterStrikeGameMode.generated.h"

class ASurvivalPlayerCharacter;
/**
 * 传统CS游戏模式
 */
UCLASS()
class SURVIVAL_API ACounterStrikeGameMode : public ATotalGameModeBase
{
	GENERATED_BODY()

public:
	virtual void PostLogin(APlayerController* NewPlayer) override;;
	virtual void RestartPlayer(AController* NewPlayer) override;

	virtual void PlayerEliminated(ASurvivalCharacterBase* EliminatedCharacter,
	                              ASurvivalPlayerController* VictimController,
	                              ASurvivalPlayerController* AttackerController) override;

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Team")
	TSubclassOf<ASurvivalPlayerCharacter> RedTeamCharacterClass;
	UPROPERTY(EditDefaultsOnly, Category = "Team")
	TSubclassOf<ASurvivalPlayerCharacter> BlueTeamCharacterClass;
};
