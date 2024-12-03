// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "SurvivalPlayerController.generated.h"

struct FInputActionValue;
class UInputAction;
class UInputMappingContext;
/**
 * 
 */
UCLASS()
class SURVIVAL_API ASurvivalPlayerController : public APlayerController
{
	GENERATED_BODY()
public:
	virtual void BeginPlay() override;
protected:
	virtual void SetupInputComponent() override;
	
	//~Begin Input
	void ForwardInputMove(const FInputActionValue& Value);
	void ForwardInputLook(const FInputActionValue& Value);
	void ForwardInputShootStarted(const FInputActionValue& Value);
	void ForwardInputShootCompleted(const FInputActionValue& Value);
	UPROPERTY(EditAnywhere,Category = "Input")
	TObjectPtr<UInputMappingContext> DefaultMappingContext;
	UPROPERTY(EditAnywhere,Category = "Input")
	TObjectPtr<UInputAction> ActionMove;
	UPROPERTY(EditAnywhere,Category = "Input")
	TObjectPtr<UInputAction> ActionLook;
	UPROPERTY(EditAnywhere,Category = "Input")
	TObjectPtr<UInputAction> ActionShoot;
	//~End Input
};
