// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "SurvivalPlayerState.generated.h"

class UAbilityComponent;
/**
 * 
 */
UCLASS()
class SURVIVAL_API ASurvivalPlayerState : public APlayerState
{
	GENERATED_BODY()

public:
	ASurvivalPlayerState();
	
	UAbilityComponent* GetAbilityComponent() const;
protected:
	UPROPERTY(VisibleAnywhere, Category = "Ability")
	TObjectPtr<UAbilityComponent> AbilityComponent;
};
