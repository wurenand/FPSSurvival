// Fill out your copyright notice in the Description page of Project Settings.


#include "Survival/Public/Player/SurvivalPlayerController.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Character/SurvivalPlayerCharacter.h"
#include "Player/SurvivalPlayerState.h"
#include "Game/SurvivalGameState.h"
#include "Interface/HandleInputInterface.h"
#include "UI/HUD/TotalHUD.h"
#include "UI/WidgetController/TotalWidgetController.h"

void ASurvivalPlayerController::BeginPlay()
{
	Super::BeginPlay();
	checkf(DefaultMappingContext, TEXT("DefaultMappingContext is NULL"));
	if (UEnhancedInputLocalPlayerSubsystem* EISubsystem = ULocalPlayer::GetSubsystem<
		UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		EISubsystem->AddMappingContext(DefaultMappingContext, 0);
	}
	//初始化UI
	if (IsLocalController())
	{
		if (ATotalHUD* TotalHUD = Cast<ATotalHUD>(GetHUD()))
		{
			FBaseWidgetControllerParams Params;
			Params.Character = Cast<ASurvivalPlayerCharacter>(GetCharacter());
			Params.PlayerState = GetPlayerState<ASurvivalPlayerState>();
			Params.TotalGameState = GetWorld()->GetGameState<ATotalGameStateBase>();
			Params.PlayerController = this;
			TotalHUD->InitializeOverlay(Params);
		}
	}
}

void ASurvivalPlayerController::CL_AttackHit_Implementation()
{
	OnAttackHitDelegate.Broadcast(0);
	//TODO:后续还可以添加音效等...
}

void ASurvivalPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	//绑定IA
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent))
	{
		EnhancedInputComponent->BindAction(ActionMove, ETriggerEvent::Triggered, this,
		                                   &ASurvivalPlayerController::ForwardInputMove);
		EnhancedInputComponent->BindAction(ActionLook, ETriggerEvent::Triggered, this,
		                                   &ASurvivalPlayerController::ForwardInputLook);
		EnhancedInputComponent->BindAction(ActionShoot, ETriggerEvent::Triggered, this,
		                                   &ASurvivalPlayerController::ForwardInputShootTriggered);
		EnhancedInputComponent->BindAction(ActionShoot, ETriggerEvent::Completed, this,
		                                   &ASurvivalPlayerController::ForwardInputShootCompleted);
		EnhancedInputComponent->BindAction(ActionReload, ETriggerEvent::Started, this,
		                                   &ASurvivalPlayerController::ForwardInputReload);
	}
}

void ASurvivalPlayerController::ChangeOverlayPage_Implementation(FName PageName)
{
	if (ATotalHUD* HUD = Cast<ATotalHUD>(GetHUD()))
	{
		HUD->ChangeOverlayPage(PageName);
	}
}

void ASurvivalPlayerController::SRV_UpdateAimDirection_Implementation()
{
	if (!IsValid(GetPawn()))
	{
		return;
	}
	if (ASurvivalPlayerCharacter* PlayerCharacter = Cast<ASurvivalPlayerCharacter>(GetPawn()))
	{
		//Controller 的 ActorRotation被隐藏了
		//Controller的ControllerRotation是被同步的 (具体在哪不知道 AddControllerInput?)
		float AO_Pitch = GetControlRotation().Pitch;
		if (AO_Pitch >= 90.f)
		{
			FVector2D InRange(270.f, 360.f);
			FVector2D OutRange(-90.f, 0.f);
			AO_Pitch = FMath::GetMappedRangeValueClamped(InRange, OutRange, AO_Pitch);
		}
		PlayerCharacter->AimDirection = AO_Pitch;
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
		SRV_UpdateAimDirection();
	}
}

void ASurvivalPlayerController::ForwardInputShootTriggered(const FInputActionValue& Value)
{
	if (IHandleInputInterface* Interface = Cast<IHandleInputInterface>(GetPawn()))
	{
		Interface->HandleInputShootTriggered(Value);
	}
}

void ASurvivalPlayerController::ForwardInputShootCompleted(const FInputActionValue& Value)
{
	if (IHandleInputInterface* Interface = Cast<IHandleInputInterface>(GetPawn()))
	{
		Interface->HandleInputShootCompleted(Value);
	}
}

void ASurvivalPlayerController::ForwardInputReload(const FInputActionValue& Value)
{
	if (IHandleInputInterface* Interface = Cast<IHandleInputInterface>(GetPawn()))
	{
		Interface->HandleInputReload(Value);
	}
}
