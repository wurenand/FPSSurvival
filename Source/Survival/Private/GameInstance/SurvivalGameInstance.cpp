// Fill out your copyright notice in the Description page of Project Settings.


#include "GameInstance/SurvivalGameInstance.h"
#include "Blueprint/UserWidget.h"

void USurvivalGameInstance::Init()
{
	Super::Init();
	FCoreUObjectDelegates::PreLoadMap.AddUObject(this, &USurvivalGameInstance::StartLoading);
	FCoreUObjectDelegates::PostLoadMapWithWorld.AddUObject(this, &USurvivalGameInstance::EndLoading);
}

void USurvivalGameInstance::StartLoading(const FString& MapName)
{
	GetLoadingWidget()->AddToViewport();
}

void USurvivalGameInstance::EndLoading(UWorld* World)
{
	GetLoadingWidget()->RemoveFromParent();
}

UUserWidget* USurvivalGameInstance::GetLoadingWidget()
{
	if (LoadingWidget == nullptr)
	{
		if (LoadingWidgetClass != nullptr)
		{
			LoadingWidget = CreateWidget<UUserWidget>(this, LoadingWidgetClass);
		}
	}
	return LoadingWidget;
}
