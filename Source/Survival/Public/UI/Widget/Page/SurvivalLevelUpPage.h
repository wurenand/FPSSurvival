// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/Widget/SurvivalUserWidget.h"
#include "SurvivalLevelUpPage.generated.h"

class UAbilityWidget;
struct FAbilityDataTableRow;
class UAbilityComponent;
class UVerticalBox;
class USurvivalWidgetController;
/**
 * 
 */
UCLASS()
class SURVIVAL_API USurvivalLevelUpPage : public USurvivalUserWidget
{
	GENERATED_BODY()

public:
	USurvivalLevelUpPage();

	//刷新Options
	void ReFreshOptions(UAbilityComponent* AbilityComponent, int32 OptionCount = 2);
	virtual void AfterChooseThisPage_Implementation() override;

protected:
	UPROPERTY(meta = (BindWidget))
	UVerticalBox* VB_Options;

	TArray<FAbilityDataTableRow*> AbilityDataRows;

	UPROPERTY(EditDefaultsOnly,Category = "Class")
	TSubclassOf<UAbilityWidget> AbilityWidgetClass;
};
