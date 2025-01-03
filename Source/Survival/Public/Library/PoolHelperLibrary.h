// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "PoolHelperLibrary.generated.h"

class ASurvivalPlayerState;
class UObjectPoolComponent;
/**
 * 辅助拿到GameMode中的Pool
 */
UCLASS()
class SURVIVAL_API UPoolHelperLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	public:
	UFUNCTION()
	static UObjectPoolComponent* GetProjectilePool(APlayerState* PlayerState,UClass* ProjectileClass);
};
