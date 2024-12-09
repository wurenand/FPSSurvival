// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "SurvivalGameInstance.generated.h"

class USurvivalUserWidget;
/**
 * 
 */
UCLASS()
class SURVIVAL_API USurvivalGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	virtual void Init() override;
	
	void StartLoading(const FString& MapName);
	void EndLoading(UWorld* World);
	
protected:
	UPROPERTY(EditAnywhere)
	TSubclassOf<UUserWidget> LoadingWidgetClass;
	UPROPERTY()
	TObjectPtr<UUserWidget> LoadingWidget;

private:
	UUserWidget* GetLoadingWidget();
};
