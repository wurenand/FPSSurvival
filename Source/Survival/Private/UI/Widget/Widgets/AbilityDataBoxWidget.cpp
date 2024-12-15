// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/Widget/Widgets/AbilityDataBoxWidget.h"

#include "Components/TextBlock.h"

void UAbilityDataBoxWidget::SetInfo(const FName& InDataName, const FRealCurve* Curve, int32 CurrentLevel)
{
	DataName->SetText(FText::FromString(InDataName.ToString()));
	DataPreValue->SetText(FText::AsNumber(Curve->Eval(CurrentLevel)));
	DataNewValue->SetText(FText::AsNumber(Curve->Eval(CurrentLevel + 1)));
}
