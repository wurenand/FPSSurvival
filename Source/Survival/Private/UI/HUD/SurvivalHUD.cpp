// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/HUD/SurvivalHUD.h"

#include "Game/SurvivalGameState.h"
#include "UI/Widget/Page/SurvivalLevelUpPage.h"
#include "UI/WidgetController/SurvivalWidgetController.h"

void ASurvivalHUD::SetWidgetControllerParams(const FBaseWidgetControllerParams& Params)
{
	Super::SetWidgetControllerParams(Params);
	USurvivalWidgetController* SurvivalWidgetController = Cast<USurvivalWidgetController>(WidgetController);
	SurvivalWidgetController->SurvivalGameState = Cast<ASurvivalGameState>(Params.TotalGameState);
}

void ASurvivalHUD::GetOptions(UAbilityComponent* AbilityComponent)
{
	if (USurvivalLevelUpPage* SurvivalLevelUpPage = Cast<USurvivalLevelUpPage>(NameToOverlayWidgets[TEXT("LevelUp")]))
	{
		SurvivalLevelUpPage->ReFreshOptions(AbilityComponent);
	}
}
