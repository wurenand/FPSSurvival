// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/HUD/CounterStrikeHUD.h"

#include "Game/CounterStrikeGameState.h"
#include "UI/WidgetController/CounterStrikeWidgetController.h"
#include "UI/WidgetController/TotalWidgetController.h"


void ACounterStrikeHUD::SetWidgetControllerParams(const FBaseWidgetControllerParams& Params)
{
	Super::SetWidgetControllerParams(Params);
	UCounterStrikeWidgetController* CounterStrikeWidgetController = Cast<UCounterStrikeWidgetController>(WidgetController);
	CounterStrikeWidgetController->CounterStrikeGameState = Cast<ACounterStrikeGameState>(Params.TotalGameState);
}
