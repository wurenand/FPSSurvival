// Fill out your copyright notice in the Description page of Project Settings.


#include "GameInstance/SurvivalGameInstance.h"


#include "MoviePlayer.h"
#include "Blueprint/UserWidget.h"

void USurvivalGameInstance::Init()
{
	Super::Init();
	FCoreUObjectDelegates::PreLoadMap.AddUObject(this, &USurvivalGameInstance::StartLoading);
	FCoreUObjectDelegates::PostLoadMapWithWorld.AddUObject(this, &USurvivalGameInstance::EndLoading);
}

//这个函数原本会被主线程阻塞，因为在LoadMap过程中会一直执行LoadMap逻辑，这两个Start和End的Callback
//会一直被阻塞到最后，导致连续执行，看不见UI。所以使用MoviePlayer实现UMG在Slate线程显示，不再被阻塞
void USurvivalGameInstance::StartLoading(const FString& MapName)
{
	FLoadingScreenAttributes LoadingScreen;
	//配置属性
	//加载完成时结束播放
	LoadingScreen.bAutoCompleteWhenLoadingCompletes = true;
	LoadingScreen.WidgetLoadingScreen = GetLoadingWidget()->TakeWidget();
	GetMoviePlayer()->SetupLoadingScreen(LoadingScreen);
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
