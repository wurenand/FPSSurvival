// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/HUD/TotalHUD.h"
#include "SurvivalHUD.generated.h"

class UAbilityComponent;
class UCounterStrikeWidgetController;
/**
 * 
 */
UCLASS()
class SURVIVAL_API ASurvivalHUD : public ATotalHUD
{
	GENERATED_BODY()
public:
	virtual void SetWidgetControllerParams(const FBaseWidgetControllerParams& Params) override;
	void GetOptions(UAbilityComponent* AbilityComponent);
};
