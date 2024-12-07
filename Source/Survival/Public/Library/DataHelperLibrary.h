// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "DataHelperLibrary.generated.h"

class ASurvivalGameState;
class UDataManager;
struct FWeaponInfo;
/**
 * 
 */
UCLASS()
class SURVIVAL_API UDataHelperLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "DataHelperLibrary")
	static FWeaponInfo GetWeaponInfoFromName(const UObject* WorldContentObject,const FName& WeaponName);

};
