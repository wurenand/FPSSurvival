// Fill out your copyright notice in the Description page of Project Settings.


#include "Survival/Public/Character/SurvivalCharacterBase.h"

#include "Components/CapsuleComponent.h"
#include "GameFramework/PawnMovementComponent.h"
#include "Net/UnrealNetwork.h"

ASurvivalCharacterBase::ASurvivalCharacterBase()
{
	
}

void ASurvivalCharacterBase::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(ASurvivalCharacterBase,MaxHealth);
	DOREPLIFETIME(ASurvivalCharacterBase,Health);
}

void ASurvivalCharacterBase::InitializeAttributes()
{
	
}

ETeam ASurvivalCharacterBase::GetCharacterTeam()
{
	return Team;
}

void ASurvivalCharacterBase::CombatTakeDamage(ASurvivalCharacterBase* DamageInstigator, float DamageValue)
{
	
}

void ASurvivalCharacterBase::SetPendingDeath()
{
	Mult_DeathEffect();
}

void ASurvivalCharacterBase::Mult_DeathEffect_Implementation()
{
	//实现类似布娃娃系统的效果
	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	GetMesh()->SetCollisionEnabled(ECollisionEnabled::Type::PhysicsOnly);
	GetMesh()->SetSimulatePhysics(true);
	GetMovementComponent()->StopMovementImmediately();
}

void ASurvivalCharacterBase::OnRep_MaxHealth()
{
	//TODO:更新UI
}

void ASurvivalCharacterBase::OnRep_Health()
{
	//TODO:更新UI
}
