// Fill out your copyright notice in the Description page of Project Settings.


#include "Anim/CharacterAnimInstance.h"

#include "KismetAnimationLibrary.h"
#include "Character/SurvivalCharacterBase.h"
#include "Character/SurvivalPlayerCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"

void UCharacterAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();
	GetCharacterBase();
}

void UCharacterAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);
	if (GetCharacterBase())
	{
		FVector Velocity = GetCharacterBase()->GetVelocity();
		MovementSpeed = Velocity.Length();
		MovementDirection = UKismetAnimationLibrary::CalculateDirection(Velocity,GetCharacterBase()->GetActorRotation());
		if (ASurvivalPlayerCharacter* Player = Cast<ASurvivalPlayerCharacter>(GetCharacterBase()))
		{
			AimDirection = Player->AimDirection;
		}
		bIsInAir = GetCharacterBase()->GetCharacterMovement()->IsFalling();
	}
}

ASurvivalCharacterBase* UCharacterAnimInstance::GetCharacterBase()
{
	if (IsValid(CharacterBase))
	{
		return CharacterBase;
	}
	CharacterBase = Cast<ASurvivalCharacterBase>(TryGetPawnOwner());
	return CharacterBase;
}
