// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "AnimNotify_SetAttackEnabled.generated.h"

/**
 * 用来在蒙太奇中通知AI是否开启Attack碰撞检测
 */
UCLASS()
class SURVIVAL_API UAnimNotify_SetAttackEnabled : public UAnimNotify
{
	GENERATED_BODY()
protected:
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	bool bIsAttackEnabled;
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;
};
