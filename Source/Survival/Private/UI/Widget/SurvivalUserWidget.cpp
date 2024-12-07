// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Widget/SurvivalUserWidget.h"

void USurvivalUserWidget::SetWidgetController(UObject* InWidgetController)
{
	WidgetController = InWidgetController;
	AfterWidgetControllerSet();
}
