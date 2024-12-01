// Fill out your copyright notice in the Description page of Project Settings.


#include "Survival/Public/Character/SurvivalCharacterBase.h"


// Sets default values
ASurvivalCharacterBase::ASurvivalCharacterBase()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ASurvivalCharacterBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASurvivalCharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void ASurvivalCharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

