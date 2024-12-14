// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SurvivalUserWidget.generated.h"

/**
 * Widget基类 提供一个UObject作为WidgetController 实现基于MVC框架的显示
 */
UCLASS()
class SURVIVAL_API USurvivalUserWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	//提供给UI创建者（PC）用来设置WidgetController的函数
	UFUNCTION(BlueprintCallable)
	void SetWidgetController(UObject* InWidgetController);

	//提供给HUD进行切换使用的标识，注意不要重复。
	UPROPERTY(EditAnywhere,Category = "PageInfo")
	FName PageName = TEXT("");
	//由HUD负责调用，当切换到当前页面时调用，蓝图中用来设置InputMode等..
	UFUNCTION(BlueprintNativeEvent)//默认会提供一个_Implementation的virtual函数
	void AfterChooseThisPage();
protected:
	UPROPERTY(BlueprintReadOnly, Category = "Controller")
	TObjectPtr<UObject> WidgetController;
	//在蓝图中实现，在WidgetController被设置后调用，绑定函数到WidgetController中的Delegate来更新数据等
	UFUNCTION(BlueprintNativeEvent)
	void AfterWidgetControllerSet();
};
