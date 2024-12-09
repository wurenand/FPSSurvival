// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "TotalHUD.generated.h"

class ASurvivalPlayerCharacter;
class UTotalWidgetController;
struct FBaseWidgetControllerParams;
class USurvivalUserWidget;
/**
 * HUD的基类
 * 负责初始化所有Overlay Page
 * 创建绑定WidgetController
 * 切换Overlay Page
 */
UCLASS()
class SURVIVAL_API ATotalHUD : public AHUD
{
	GENERATED_BODY()

public:
	//传入WidgetController可能需要的参数
	virtual void InitializeOverlay(const FBaseWidgetControllerParams& Params);

	//~Begin PC Control
	//由PC调用，切换当前Overlay显示的界面
	void ChangeOverlayPage(FName PageName);
	//~End PC Control

	//~Begin WidgetControllerParam
	//在InitializeOverlay中调用，由子类重写，给WidgetController设置所需的Param
	virtual void SetWidgetControllerParams(const FBaseWidgetControllerParams& Params);
	//提供给外部调用，当Character发生变化时，会通知绑定的Overlay (Character生命周期管理)
	void UpdateParamCharacter(ASurvivalPlayerCharacter* PlayerCharacter);
	//~End WidgetControllerParam

	UPROPERTY()
	TMap<FName, TObjectPtr<USurvivalUserWidget>> NameToOverlayWidgets;
	UPROPERTY()
	TObjectPtr<UTotalWidgetController> WidgetController;

protected:
	//在所有Overlay中要默认显示的PageName
	UPROPERTY(EditAnywhere,Category = "ClassInfo")
	FName DefaultName = TEXT("");
	//记录所有要Spawn的各种PageOverlayClass
	UPROPERTY(EditAnywhere, Category = "ClassInfo")
	TArray<TSubclassOf<USurvivalUserWidget>> OverlayWidgetClasses;
	UPROPERTY(EditAnywhere, Category = "ClassInfo")
	TSubclassOf<UTotalWidgetController> WidgetControllerClass;
};
