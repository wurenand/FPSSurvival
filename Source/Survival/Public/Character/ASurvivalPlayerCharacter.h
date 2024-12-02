// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SurvivalCharacterBase.h"
#include "Interface/HandleInputInterface.h"
#include "ASurvivalPlayerCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;

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

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Camera")
	TObjectPtr<UCameraComponent> Camera;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Camera")
	TObjectPtr<USpringArmComponent> SpringArm;
};
