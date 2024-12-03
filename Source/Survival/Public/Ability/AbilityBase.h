// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "AbilityBase.generated.h"

/**
 * 
 */
UCLASS()
class SURVIVAL_API UAbilityBase : public UObject
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Ability")
	FName AbilityName;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Ability")
	int32 Level;
};
