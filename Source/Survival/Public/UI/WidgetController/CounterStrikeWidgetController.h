// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/WidgetController/TotalWidgetController.h"
#include "CounterStrikeWidgetController.generated.h"

class ACounterStrikeGameState;
class ASurvivalPlayerCharacter;
/**
 * 
 */
UCLASS()
class SURVIVAL_API UCounterStrikeWidgetController : public UTotalWidgetController
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadOnly,Category = "Params")
	TObjectPtr<ACounterStrikeGameState> CounterStrikeGameState;
};
