// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "HandleInputInterface.generated.h"

struct FGameplayTag;
struct FInputActionValue;
// This class does not need to be modified.
UINTERFACE()
class UHandleInputInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 转发PC的输入
 */
class SURVIVAL_API IHandleInputInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual void HandleInputMove(const FInputActionValue& Value) = 0;
	virtual void HandleInputLook(const FInputActionValue& Value) = 0;
	virtual void HandleInputJump(const FInputActionValue& Value) = 0;
	//输入Triggered/Completed会调用的函数
	virtual void HandleInputTagInputTriggered(FGameplayTag InputTag) = 0;
};
