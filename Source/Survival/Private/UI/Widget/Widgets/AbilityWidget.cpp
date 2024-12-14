// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Widget/Widgets/AbilityWidget.h"

#include "Components/Button.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Library/DataHelperLibrary.h"
#include "Player/SurvivalPlayerController.h"
#include "UI/Widget/Page/SurvivalLevelUpPage.h"

void UAbilityWidget::NativeConstruct()
{
	Super::NativeConstruct();
	Button_SelectAbility->OnPressed.AddDynamic(this, &UAbilityWidget::SelectAbility);
}

void UAbilityWidget::SetInfo(FName AbilityName, int32 CurrentLevel)
{
	FAbilityDataTableRow Row = UDataHelperLibrary::GetAbilityDataFromName(GetWorld(), AbilityName);
	Image_Icon->SetBrushFromTexture(Row.AbilityIcon);
	Text_AbilityName->SetText(FText::FromName(AbilityName));
	if (CurrentLevel == 0)
	{
		Text_AbilityLevel->SetText(FText::FromString("New!"));
	}
	else
	{
		Text_AbilityLevel->SetText(FText::AsNumber(CurrentLevel + 1));
	}
	//TODO:显示Data
}

void UAbilityWidget::SelectAbility()
{
	if (ASurvivalPlayerController* SurvivalPlayerController = Cast<ASurvivalPlayerController>(
		GetWorld()->GetFirstPlayerController()))
	{
		SurvivalPlayerController->SRV_SelectAbility(FName(Text_AbilityName->GetText().ToString()));
		SurvivalLevelUpPage->AfterSelectAbility();
	}
}
