// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SurvivalCharacterBase.h"
#include "Interface/HandleInputInterface.h"
#include "ASurvivalPlayerCharacter.generated.h"

UCLASS()
class SURVIVAL_API AASurvivalPlayerCharacter : public ASurvivalCharacterBase,public IHandleInputInterface
{
	GENERATED_BODY()

public:
	AASurvivalPlayerCharacter();

	//~Begin InputComponent
	virtual void HandleInputMove(const FInputActionValue& Value) override;
	virtual void HandleInputLook(const FInputActionValue& Value) override;
	virtual void HandleInputShoot(const FInputActionValue& Value) override;
	//~End InputComponent
	
protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};
