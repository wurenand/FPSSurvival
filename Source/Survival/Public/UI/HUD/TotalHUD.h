// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "TotalHUD.generated.h"

class UTotalWidgetController;
struct FBaseWidgetControllerParams;
class USurvivalUserWidget;
/**
 * HUD的基类，提供InitializeOverlay的功能
 * 包含Overlay的Class WidgetController的Class
 */
UCLASS()
class SURVIVAL_API ATotalHUD : public AHUD
{
	GENERATED_BODY()

public:
	//传入WidgetController可能需要的参数
	virtual void InitializeOverlay(const FBaseWidgetControllerParams& Params);

	//在InitializeOverlay中调用，由子类重写，给WidgetController设置所需的Param
	virtual void SetWidgetControllerParams(const FBaseWidgetControllerParams& Params);
	UPROPERTY()
	TObjectPtr<USurvivalUserWidget> OverlayWidget;
	UPROPERTY()
	TObjectPtr<UTotalWidgetController> WidgetController;

	protected:
	UPROPERTY(EditAnywhere,Category = "ClassInfo")
	TSubclassOf<USurvivalUserWidget> OverlayWidgetClass;
	UPROPERTY(EditAnywhere,Category = "ClassInfo")
	TSubclassOf<UTotalWidgetController> WidgetControllerClass;
};
