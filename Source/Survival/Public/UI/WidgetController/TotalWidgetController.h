// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "TotalWidgetController.generated.h"

class ASurvivalPlayerController;
class ASurvivalPlayerCharacter;
class ASurvivalCharacterBase;
class ASurvivalPlayerState;
class ATotalGameStateBase;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnCharacterUpdated, ASurvivalPlayerCharacter*, character);

USTRUCT(BlueprintType)
struct FBaseWidgetControllerParams
{
	GENERATED_BODY()
public:
	TObjectPtr<ATotalGameStateBase> TotalGameState;
	TObjectPtr<ASurvivalPlayerState> PlayerState;
	TObjectPtr<ASurvivalPlayerController> PlayerController;
	TObjectPtr<ASurvivalCharacterBase> Character;
};

/**
 * 
 */
UCLASS(BlueprintType)
class SURVIVAL_API UTotalWidgetController : public UObject
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintAssignable)
	FOnCharacterUpdated OnCharacterUpdatedDelegate;
	
	UPROPERTY(BlueprintReadOnly, Category = "Info")
	TObjectPtr<ASurvivalPlayerCharacter> Character;
	UPROPERTY(BlueprintReadOnly, Category = "Info")
	TObjectPtr<ASurvivalPlayerState> PlayerState;
	UPROPERTY(BlueprintReadOnly, Category = "Info")
	TObjectPtr<ASurvivalPlayerController> PlayerController;
};
