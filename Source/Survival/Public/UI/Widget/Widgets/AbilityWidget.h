// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/Widget/SurvivalUserWidget.h"
#include "AbilityWidget.generated.h"

class USurvivalLevelUpPage;
class UButton;
class UVerticalBox;
class UTextBlock;
class UImage;
/**
 * 
 */
UCLASS()
class SURVIVAL_API UAbilityWidget : public USurvivalUserWidget
{
	GENERATED_BODY()
public:
	virtual void NativeConstruct() override;
	//用于装入信息
	void SetInfo(FName AbilityName,int32 CurrentLevel);
	
	TObjectPtr<USurvivalLevelUpPage> SurvivalLevelUpPage;
	
protected:
	UFUNCTION()
	void SelectAbility();
	
	UPROPERTY(meta = (BindWidget))
	UButton* Button_SelectAbility;
	UPROPERTY(meta = (BindWidget))
	UImage* Image_Icon;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* Text_AbilityName;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* Text_AbilityLevel;
	UPROPERTY(meta = (BindWidget))
	UVerticalBox* VB_AbilityData;
};
