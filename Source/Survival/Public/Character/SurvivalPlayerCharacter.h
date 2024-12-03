// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SurvivalCharacterBase.h"
#include "Interface/HandleInputInterface.h"
#include "SurvivalPlayerCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;

UCLASS()
class SURVIVAL_API ASurvivalPlayerCharacter : public ASurvivalCharacterBase, public IHandleInputInterface
{
	GENERATED_BODY()

public:
	ASurvivalPlayerCharacter();

	//~Begin InputComponent
	virtual void HandleInputMove(const FInputActionValue& Value) override;
	virtual void HandleInputLook(const FInputActionValue& Value) override;
	virtual void HandleInputShoot(const FInputActionValue& Value) override;
	//~End InputComponent

	virtual void BeginPlay() override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Camera")
	TObjectPtr<UCameraComponent> Camera;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Camera")
	TObjectPtr<USpringArmComponent> SpringArm;
	//第三人称Mesh，为了解决隐藏第一人称头部导致的阴影消失问题，只做显示阴影使用！
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category ="Mesh")
	TObjectPtr<USkeletalMeshComponent> ThirdPersonMesh;
};

