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
		checkf(OverlayWidgetClass, TEXT("HUD:OverlayWidgetClass Is Null"));
		checkf(WidgetControllerClass, TEXT("HUD:OverlayWidgetClass Is Null"));
		UUserWidget* Widget = CreateWidget<UUserWidget>(GetOwningPlayerController(), OverlayWidgetClass);
		WidgetController = NewObject<UTotalWidgetController>(this, WidgetControllerClass);
		OverlayWidget = CastChecked<USurvivalUserWidget>(Widget);
		//设置参数
		SetWidgetControllerParams(Params);
		OverlayWidget->SetWidgetController(WidgetController);
		//TODO:值可以在这里广播初始化？
		OverlayWidget->AddToViewport(0);
	}
}

void ATotalHUD::SetWidgetControllerParams(const FBaseWidgetControllerParams& Params)
{
	//子类负责设置自己需要的信息来源
	WidgetController->Character = Cast<ASurvivalPlayerCharacter>(Params.Character);
}
