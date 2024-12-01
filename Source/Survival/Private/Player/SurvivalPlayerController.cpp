// Fill out your copyright notice in the Description page of Project Settings.


#include "Survival/Public/Player/SurvivalPlayerController.h"

#include "EnhancedInputSubsystems.h"

void ASurvivalPlayerController::BeginPlay()
{
	Super::BeginPlay();
	checkf(DefaultMappingContext,TEXT("DefaultMappingContext is NULL"));
	if (UEnhancedInputLocalPlayerSubsystem* EISubsystem = ULocalPlayer::GetSubsystem<
		UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		EISubsystem->AddMappingContext(DefaultMappingContext, 0);
	}
}

void ASurvivalPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	//TODO:Bind InputAction
}
