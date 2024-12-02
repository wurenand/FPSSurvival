// Fill out your copyright notice in the Description page of Project Settings.


#include "Survival/Public/Player/SurvivalPlayerController.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Interface/HandleInputInterface.h"

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
	//绑定IA
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent))
	{
		EnhancedInputComponent->BindAction(ActionMove,ETriggerEvent::Triggered,this,&ASurvivalPlayerController::ForwardInputMove);
		EnhancedInputComponent->BindAction(ActionLook,ETriggerEvent::Triggered,this,&ASurvivalPlayerController::ForwardInputLook);
		EnhancedInputComponent->BindAction(ActionShoot,ETriggerEvent::Triggered,this,&ASurvivalPlayerController::ForwardInputShoot);
	}
}

void ASurvivalPlayerController::ForwardInputMove(const FInputActionValue& Value)
{
	if (IHandleInputInterface* Interface = Cast<IHandleInputInterface>(GetPawn()))
	{
		Interface->HandleInputMove(Value);
	}
}

void ASurvivalPlayerController::ForwardInputLook(const FInputActionValue& Value)
{
	if (IHandleInputInterface* Interface = Cast<IHandleInputInterface>(GetPawn()))
	{
		Interface->HandleInputLook(Value);
	}
}

void ASurvivalPlayerController::ForwardInputShoot(const FInputActionValue& Value)
{
	if (IHandleInputInterface* Interface = Cast<IHandleInputInterface>(GetPawn()))
	{
		Interface->HandleInputShoot(Value);
	}
}
