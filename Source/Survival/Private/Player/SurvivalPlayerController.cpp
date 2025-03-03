// Fill out your copyright notice in the Description page of Project Settings.


#include "Survival/Public/Player/SurvivalPlayerController.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "GameplayTagContainer.h"
#include "Character/SurvivalPlayerCharacter.h"
#include "Components/AbilityComponent.h"
#include "Game/SurvivalGameMode.h"
#include "Player/SurvivalPlayerState.h"
#include "Game/SurvivalGameState.h"
#include "Interface/HandleInputInterface.h"
#include "UI/HUD/SurvivalHUD.h"
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
	TryInitializeHUDorParams();
}

void ASurvivalPlayerController::CL_ChangeOverlayPage_Implementation(FName PageName)
{
	if (ATotalHUD* HUD = Cast<ATotalHUD>(GetHUD()))
	{
		HUD->ChangeOverlayPage(PageName);
	}
}

void ASurvivalPlayerController::CL_AttackHit_Implementation()
{
	OnAttackHitDelegate.Broadcast(0);
	//TODO:后续还可以添加音效等...
}

void ASurvivalPlayerController::CL_HandleLevelUp_Implementation()
{
	if (ASurvivalHUD* SurvivalHUD = Cast<ASurvivalHUD>(GetHUD()))
	{
		//TODO:GA
		//SurvivalHUD->GetOptions(GetPlayerState<ASurvivalPlayerState>()->GetAbilityComponent());
	}
	CL_ChangeOverlayPage(TEXT("LevelUp"));
}

void ASurvivalPlayerController::ResumePause()
{
	if (ASurvivalGameMode* SurvivalGameMode = Cast<ASurvivalGameMode>(GetWorld()->GetAuthGameMode()))
	{
		//TODO:Every Player Should Resume Game Here
		SurvivalGameMode->PlayerResume(this);
	}
}

void ASurvivalPlayerController::SRV_SelectAbility_Implementation(FName AbilityName)
{
	//TODO:GA
	/*if (ASurvivalPlayerState* SurvivalPlayerState = GetPlayerState<ASurvivalPlayerState>())
	{
		//升级
		SurvivalPlayerState->GetAbilityComponent()->TryLevelUpAbility(AbilityName);
		//申请继续
		ResumePause();
	}*/
}

void ASurvivalPlayerController::TryInitializeHUDorParams()
{
	if (IsLocalController())
	{
		if (ATotalHUD* TotalHUD = Cast<ATotalHUD>(GetHUD()))
		{
			FBaseWidgetControllerParams Params;
			Params.Character = Cast<ASurvivalPlayerCharacter>(GetCharacter());
			Params.PlayerState = GetPlayerState<ASurvivalPlayerState>();
			Params.TotalGameState = GetWorld()->GetGameState<ATotalGameStateBase>();
			Params.PlayerController = this;
			if (!TotalHUD->bIsInitialized)
			{
				TotalHUD->InitializeOverlay(Params);
			}
			else
			{
				TotalHUD->SetWidgetControllerParams(Params);
			}
		}
	}
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
		EnhancedInputComponent->BindAction(ActionReload, ETriggerEvent::Started, this,
		                                   &ASurvivalPlayerController::ForwardInputReload);
		EnhancedInputComponent->BindAction(ActionJump, ETriggerEvent::Started, this,
		                                   &ASurvivalPlayerController::ForwardInputJump);
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
		Interface->HandleInputTagInputTriggered(FGameplayTag::RequestGameplayTag(FName("Input.LMB")));
	}
}

void ASurvivalPlayerController::ForwardInputReload(const FInputActionValue& Value)
{
	if (IHandleInputInterface* Interface = Cast<IHandleInputInterface>(GetPawn()))
	{
		Interface->HandleInputTagInputTriggered(FGameplayTag::RequestGameplayTag(FName("Input.R")));
	}
}

void ASurvivalPlayerController::ForwardInputJump(const FInputActionValue& Value)
{
	if (IHandleInputInterface* Interface = Cast<IHandleInputInterface>(GetPawn()))
	{
		Interface->HandleInputJump(Value);
	}
}
