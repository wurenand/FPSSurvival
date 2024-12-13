// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Widget/Widgets/AbilityWidget.h"

#include "Components/Button.h"
#include "Player/SurvivalPlayerController.h"

void UAbilityWidget::NativeConstruct()
{
	Super::NativeConstruct();
	Button_SelectAbility->OnPressed.AddDynamic(this, &UAbilityWidget::SelectAbility);
}

void UAbilityWidget::SetInfo()
{
}

void UAbilityWidget::SelectAbility()
{
	if (ASurvivalPlayerController* SurvivalPlayerController = Cast<ASurvivalPlayerController>(
		GetWorld()->GetFirstPlayerController()))
	{
		//TODO:这里后续选择Ability
		//SurvivalPlayerController->
	}
}
