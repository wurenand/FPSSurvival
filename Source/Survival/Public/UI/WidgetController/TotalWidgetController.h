// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "TotalWidgetController.generated.h"

class ASurvivalPlayerCharacter;
class ASurvivalCharacterBase;
class ASurvivalPlayerState;
class ATotalGameStateBase;

USTRUCT(BlueprintType)
struct FBaseWidgetControllerParams
{
	GENERATED_BODY()
public:
	TObjectPtr<ATotalGameStateBase> TotalGameState;
	TObjectPtr<ASurvivalPlayerState> PlayerState;
	TObjectPtr<ASurvivalCharacterBase> Character;
};

/**
 * 
 */
UCLASS()
class SURVIVAL_API UTotalWidgetController : public UObject
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadOnly, Category = "Info")
	TObjectPtr<ASurvivalPlayerCharacter> Character;
};
