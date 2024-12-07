// Fill out your copyright notice in the Description page of Project Settings.


#include "Library/DataHelperLibrary.h"

#include "Actor/WeaponBase.h"
#include "Game/TotalGameStateBase.h"

FWeaponInfo UDataHelperLibrary::GetWeaponInfoFromName(const UObject* WorldContentObject,const FName& WeaponName)
{
	if (ATotalGameStateBase* GameState = Cast<ATotalGameStateBase>(WorldContentObject->GetWorld()->GetGameState()))
	{
		FString ContextString = "";
		checkf(GameState->GetDataStruct().WeaponDataTable,TEXT("GameState->WeaponDataTable Is Null"))
		return *GameState->GetDataStruct().WeaponDataTable->FindRow<FWeaponInfo>(WeaponName,ContextString);
	}
	return FWeaponInfo();
}

