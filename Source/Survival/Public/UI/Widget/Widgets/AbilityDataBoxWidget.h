// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/Widget/SurvivalUserWidget.h"
#include "AbilityDataBoxWidget.generated.h"

class UTextBlock;
/**
 * 
 */
UCLASS()
class SURVIVAL_API UAbilityDataBoxWidget : public USurvivalUserWidget
{
	GENERATED_BODY()
public:
	void SetInfo(const FName& InDataName,const FRealCurve* Curve,int32 CurrentLevel);
protected:
	UPROPERTY(meta = (BindWidget))
	UTextBlock* DataName;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* DataPreValue;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* DataNewValue;
};
