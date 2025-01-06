// Fill out your copyright notice in the Description page of Project Settings.


#include "Anim/EnemyAnimInstance.h"

#include "KismetAnimationLibrary.h"
#include "Character/SurvivalEnemyCharacter.h"


void UEnemyAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();
	EnemyCharacter = Cast<ASurvivalEnemyCharacter>(TryGetPawnOwner());
	RandomIdleIndex = FMath::RandRange(0, 2);
}

void UEnemyAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);
	if (IsValid(EnemyCharacter))
	{
		FVector Velocity = EnemyCharacter->GetVelocity();
		MovementSpeed = Velocity.Length();
		MovementDirection = UKismetAnimationLibrary::CalculateDirection(Velocity, EnemyCharacter->GetActorRotation());
	}
}