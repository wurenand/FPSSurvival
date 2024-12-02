// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/ASurvivalPlayerCharacter.h"

AASurvivalPlayerCharacter::AASurvivalPlayerCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AASurvivalPlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

void AASurvivalPlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AASurvivalPlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}


void AASurvivalPlayerCharacter::HandleInputMove(const FInputActionValue& Value)
{
	
}

void AASurvivalPlayerCharacter::HandleInputLook(const FInputActionValue& Value)
{
}

void AASurvivalPlayerCharacter::HandleInputShoot(const FInputActionValue& Value)
{
	UE_LOG(LogTemp, Warning, TEXT("AASurvivalPlayerCharacter : TRY SHOOT"));
}


