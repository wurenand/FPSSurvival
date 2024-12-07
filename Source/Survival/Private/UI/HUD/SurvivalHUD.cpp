// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/HUD/SurvivalHUD.h"

#include "Character/SurvivalPlayerCharacter.h"
#include "UI/WidgetController/CounterStrikeWidgetController.h"


void ASurvivalHUD::SetWidgetControllerParams(const FBaseWidgetControllerParams& Params)
{
	CSWidgetController = Cast<UCounterStrikeWidgetController>(WidgetController);
	CSWidgetController->Character = Cast<ASurvivalPlayerCharacter>(Params.Character);
}
