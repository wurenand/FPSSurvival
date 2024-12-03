// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "CharacterAnimInstance.generated.h"

class ASurvivalCharacterBase;
/**
 * 
 */
UCLASS()
class SURVIVAL_API UCharacterAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
public:
	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;
protected:
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Animation")
	TObjectPtr<ASurvivalCharacterBase> CharacterBase;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Animation")
	float MovementSpeed;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Animation")
	float MovementDirection;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Animation")
	float AimDirection;
	ASurvivalCharacterBase* GetCharacterBase();
};
