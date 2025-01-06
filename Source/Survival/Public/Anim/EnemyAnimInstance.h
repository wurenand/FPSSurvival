// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "EnemyAnimInstance.generated.h"

class ASurvivalEnemyCharacter;
/**
 * 
 */
UCLASS()
class SURVIVAL_API UEnemyAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
public:
	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;
	protected:
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Animation")
	float MovementSpeed;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Animation")
	float MovementDirection;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Animation")
	TObjectPtr<ASurvivalEnemyCharacter> EnemyCharacter;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Animation")
	int32 RandomIdleIndex;
};
