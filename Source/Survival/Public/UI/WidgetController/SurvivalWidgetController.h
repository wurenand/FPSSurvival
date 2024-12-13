// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/WidgetController/TotalWidgetController.h"
#include "SurvivalWidgetController.generated.h"

class ASurvivalGameState;
/**
 * 
 */
UCLASS()
class SURVIVAL_API USurvivalWidgetController : public UTotalWidgetController
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly, Category = "Params")
	TObjectPtr<ASurvivalGameState> SurvivalGameState;
};
