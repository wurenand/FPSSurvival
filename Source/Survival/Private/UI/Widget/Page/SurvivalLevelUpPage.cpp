// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Widget/Page/SurvivalLevelUpPage.h"

#include "Components/AbilityComponent.h"
#include "Components/TextBlock.h"
#include "Components/VerticalBox.h"
#include "Library/DataHelperLibrary.h"
#include "UI/Widget/Widgets/AbilityWidget.h"


USurvivalLevelUpPage::USurvivalLevelUpPage()
{
	PageName = TEXT("LevelUp");
}

void USurvivalLevelUpPage::ReFreshOptions(UAbilityComponent* AbilityComponent, int32 OptionCount)
{
	Text_Wait->SetVisibility(ESlateVisibility::Hidden);
	VB_Options->SetVisibility(ESlateVisibility::Visible);
	
	//清除之前的选项
	for (UWidget* Child : VB_Options->GetAllChildren())
	{
		Child->RemoveFromParent();
	}
	//获取所有可能的技能
	UDataTable* AbilityDataTable = UDataHelperLibrary::GetAbilityDataTable(GetWorld());
	FString ContextString = "";
	AbilityDataTable->GetAllRows<FAbilityDataTableRow>(ContextString, AbilityDataRows);
	for (int32 i = 0; i < OptionCount; i++)
	{
		int32 RandomIndex = FMath::RandRange(0, AbilityDataRows.Num() - 1);
		const FAbilityDataTableRow* Row = AbilityDataRows[RandomIndex];
		checkf(AbilityWidgetClass,TEXT("AbilityWidgetClass Is NULL"))
		UAbilityWidget* NewAbilityWidget = CreateWidget<UAbilityWidget>(GetOwningPlayer(), AbilityWidgetClass);
		NewAbilityWidget->SurvivalLevelUpPage = this;
		//判断是否已经拥有技能
		const FAbilityHandle* Handle = AbilityComponent->IsOwningAbility(Row->AbilityName);
		if (Handle)
		{
			NewAbilityWidget->SetInfo(Handle->AbilityName, Handle->Level);
		}
		else
		{
			NewAbilityWidget->SetInfo(Row->AbilityName, 0);
		}
		VB_Options->AddChild(NewAbilityWidget);
	}
}


void USurvivalLevelUpPage::AfterChooseThisPage_Implementation()
{
	GetWorld()->GetFirstPlayerController()->bShowMouseCursor = true;
}

void USurvivalLevelUpPage::AfterSelectAbility()
{
	VB_Options->SetVisibility(ESlateVisibility::Hidden);
	Text_Wait->SetVisibility(ESlateVisibility::Visible);
}
