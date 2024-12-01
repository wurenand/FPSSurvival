// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/ASurvivalPlayerCharacter.h"


// Sets default values
AASurvivalPlayerCharacter::AASurvivalPlayerCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AASurvivalPlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AASurvivalPlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void AASurvivalPlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

