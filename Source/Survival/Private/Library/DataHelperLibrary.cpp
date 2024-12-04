// Fill out your copyright notice in the Description page of Project Settings.


#include "Library/DataHelperLibrary.h"

#include "Actor/WeaponBase.h"
#include "Game/SurvivalGameState.h"

FWeaponInfo UDataHelperLibrary::GetWeaponInfoFromName(const UObject* WorldContentObject,const FName& WeaponName)
{
	if (ASurvivalGameState* GameState = Cast<ASurvivalGameState>(WorldContentObject->GetWorld()->GetGameState()))
	{
		FString ContextString = "";
		return *GameState->GetDataStruct().WeaponDataTable->FindRow<FWeaponInfo>(WeaponName,ContextString);
	}
	return FWeaponInfo();
}

