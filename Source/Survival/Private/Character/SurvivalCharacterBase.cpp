// Fill out your copyright notice in the Description page of Project Settings.


#include "Survival/Public/Character/SurvivalCharacterBase.h"
#include "Ability/GA/GameplayAbilityBase.h"
#include "Ability/SurvivalAbilitySystemComponent.h"
#include "Ability/SurvivalAttributeSet.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/PawnMovementComponent.h"
#include "Net/UnrealNetwork.h"

ASurvivalCharacterBase::ASurvivalCharacterBase()
{
}

void ASurvivalCharacterBase::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
}

void ASurvivalCharacterBase::InitializeCharacter()
{
}

void ASurvivalCharacterBase::ApplyGameplayEffectToSelf(const TSubclassOf<UGameplayEffect>& EffectToBeApplied,
                                                       float Level)
{
	if (EffectToBeApplied == nullptr || !IsValid(AbilitySystemComponent))
	{
		return;
	}
	FGameplayEffectContextHandle EffectContextHandle = AbilitySystemComponent->MakeEffectContext();
	EffectContextHandle.AddSourceObject(this);
	FGameplayEffectSpecHandle EffectSpecHandle = AbilitySystemComponent->MakeOutgoingSpec(
		EffectToBeApplied, Level, EffectContextHandle);
	AbilitySystemComponent->ApplyGameplayEffectSpecToTarget(*EffectSpecHandle.Data.Get(), AbilitySystemComponent.Get());
}

UAbilitySystemComponent* ASurvivalCharacterBase::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

UAttributeSet* ASurvivalCharacterBase::GetAttributeSet() const
{
	return AttributeSet;
}

void ASurvivalCharacterBase::GiveCharacterAbility(TSubclassOf<UGameplayAbilityBase> AbilityClass, int32 Level)
{
	if (!(GetLocalRole() == ROLE_Authority) || !IsValid(AbilitySystemComponent))
	{
		return;
	}
	FGameplayAbilitySpec Spec(AbilityClass);
	Spec.SourceObject = this;
	Spec.Level = Level;
	AbilitySystemComponent->TryGiveAbility(Spec);
}

ETeam ASurvivalCharacterBase::GetCharacterTeam()
{
	return Team;
}

void ASurvivalCharacterBase::CombatTakeDamage(ASurvivalCharacterBase* DamageInstigator, float DamageValue)
{
}

void ASurvivalCharacterBase::SetPendingDeath(bool bQuickDestroy)
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
