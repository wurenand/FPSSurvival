// Fill out your copyright notice in the Description page of Project Settings.


#include "Library/DataHelperLibrary.h"

#include "Ability/AbilityBase.h"
#include "Actor/WeaponBase.h"
#include "Game/TotalGameStateBase.h"

FWeaponInfo UDataHelperLibrary::GetWeaponInfoFromName(const UObject* WorldContentObject, const FName& WeaponName)
{
	if (ATotalGameStateBase* GameState = Cast<ATotalGameStateBase>(WorldContentObject->GetWorld()->GetGameState()))
	{
		FString ContextString = "";
		checkf(GameState->GetDataStruct().WeaponDataTable, TEXT("GameState->WeaponDataTable Is Null"))
		return *GameState->GetDataStruct().WeaponDataTable->FindRow<FWeaponInfo>(WeaponName, ContextString);
	}
	return FWeaponInfo();
}

FAbilityDataTableRow UDataHelperLibrary::GetAbilityDataFromName(const UObject* WorldContentObject,
                                                                const FName& AbilityName)
{
	if (ATotalGameStateBase* GameState = Cast<ATotalGameStateBase>(WorldContentObject->GetWorld()->GetGameState()))
	{
		FString ContextString = "";
		checkf(GameState->GetDataStruct().AbilityDataTable, TEXT("GameState->AbilityDataTable Is Null"))
		return *GameState->GetDataStruct().AbilityDataTable->FindRow<FAbilityDataTableRow>(AbilityName, ContextString);
	}
	return FAbilityDataTableRow();
}

int32 UDataHelperLibrary::GetLevelFromXP(const UObject* WorldContentObject, int32 XP)
{
	if (ATotalGameStateBase* GameState = Cast<ATotalGameStateBase>(WorldContentObject->GetWorld()->GetGameState()))
	{
		FString ContextString = ""; //TODO:这里的check好像没用？
		checkf(GameState->GetDataStruct().XPToLevelCurve, TEXT("GameState->XPToLevelCurve Is Null"))
		FRealCurve* XPCurve = GameState->GetDataStruct().XPToLevelCurve->FindCurve(TEXT("XPToLevel"), ContextString);
		int32 Level = 1;
		int32 MaxLevel = XPCurve->GetNumKeys();
		if (MaxLevel <= Level)
		{
			return Level;
		}
		while (XP >= XPCurve->Eval(Level + 1))
		{
			Level++;
		}
		return Level;
	}
	return 1;
}

float UDataHelperLibrary::GetPercentToNextLevelFromXP(const UObject* WorldContentObject, int32 XP)
{
	if (ATotalGameStateBase* GameState = Cast<ATotalGameStateBase>(WorldContentObject->GetWorld()->GetGameState()))
	{
		FString ContextString = "";
		checkf(GameState->GetDataStruct().XPToLevelCurve, TEXT("GameState->XPToLevelCurve Is Null"))
		FRealCurve* XPCurve = GameState->GetDataStruct().XPToLevelCurve->FindCurve(TEXT("XPToLevel"), ContextString);
		int32 CurrentLevel = GetLevelFromXP(WorldContentObject, XP);
		int32 BaseXP = XPCurve->Eval(CurrentLevel);
		int32 NextXP = XPCurve->Eval(CurrentLevel + 1);
		return static_cast<float>(XP - BaseXP) / (NextXP - BaseXP);
	}
	return 0;
}
