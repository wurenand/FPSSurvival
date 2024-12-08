// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/HUD/TotalHUD.h"
#include "CounterStrikeHUD.generated.h"

class ASurvivalPlayerCharacter;
/**
 * 
 */
UCLASS()
class SURVIVAL_API ACounterStrikeHUD : public ATotalHUD
{
	GENERATED_BODY()
	public:
	virtual void SetWidgetControllerParams(const FBaseWidgetControllerParams& Params) override;

};
