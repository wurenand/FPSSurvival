// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/HUD/TotalHUD.h"

#include "Character/SurvivalPlayerCharacter.h"
#include "UI/Widget/SurvivalUserWidget.h"
#include "UI/WidgetController/TotalWidgetController.h"

void ATotalHUD::InitializeOverlay(const FBaseWidgetControllerParams& Params)
{
	//只在本地SpawnUI
	if (GetOwningPlayerController()->IsLocalController())
	{
		//Spawn WidgetController
		checkf(WidgetControllerClass, TEXT("HUD:OverlayWidgetClass Is Null"));
		WidgetController = NewObject<UTotalWidgetController>(this, WidgetControllerClass);
		//设置参数
		SetWidgetControllerParams(Params);
		//Spawn Overlays
		for (auto OverlayClass : OverlayWidgetClasses)
		{
			checkf(OverlayClass, TEXT("HUD:OverlayWidgetClass Is Null"));
			UUserWidget* Widget = CreateWidget<UUserWidget>(GetOwningPlayerController(), OverlayClass);
			USurvivalUserWidget* SurvivalUserWidget = CastChecked<USurvivalUserWidget>(Widget);
			NameToOverlayWidgets.Add(SurvivalUserWidget->PageName,SurvivalUserWidget);
			SurvivalUserWidget->SetWidgetController(WidgetController);
			if (SurvivalUserWidget->PageName == DefaultName)
			{
				SurvivalUserWidget->AddToViewport();
			}
		}
	}
}

void ATotalHUD::ChangeOverlayPage(FName PageName)
{
	for (auto ItPair : NameToOverlayWidgets)
	{
		ItPair.Value->RemoveFromParent();
	}
	if (NameToOverlayWidgets.Contains(PageName))
	{
		NameToOverlayWidgets[PageName]->AddToViewport();
	}
}

void ATotalHUD::SetWidgetControllerParams(const FBaseWidgetControllerParams& Params)
{
	//子类负责设置自己需要的信息来源
	UpdateParamCharacter(Cast<ASurvivalPlayerCharacter>(Params.Character));
	WidgetController->PlayerState = Params.PlayerState;
}

void ATotalHUD::UpdateParamCharacter(ASurvivalPlayerCharacter* PlayerCharacter)
{
	if (!IsValid(WidgetController))
	{
		return;
	}
	WidgetController->Character = PlayerCharacter;
	WidgetController->OnCharacterUpdatedDelegate.Broadcast(WidgetController->Character);
}
