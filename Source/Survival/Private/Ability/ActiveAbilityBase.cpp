// Fill out your copyright notice in the Description page of Project Settings.


#include "Ability/ActiveAbilityBase.h"

#include "Actor/Projectiles/ProjectileBase.h"
#include "Character/SurvivalPlayerCharacter.h"
#include "Components/AbilityComponent.h"
#include "Library/DataHelperLibrary.h"


void UActiveAbilityBase::UpdateValues()
{
	Super::UpdateValues();
	DataTableRow = UDataHelperLibrary::GetAbilityDataFromName(AbilityComponent->SurvivalPlayerCharacter, AbilityName);
	//尝试获取Frequency的值
	GET_VALUE_FROM_CURVE_HELPER(Frequency, Level)
	GET_VALUE_FROM_CURVE_HELPER(Damage, Level)
	//重设Timer
	if (ActiveTimerHandle.IsValid())
	{
		//BUG:由于UObject没有默认的WorldContext，所以不能GetWorld()拿到世界
		GetOuter()->GetWorld()->GetTimerManager().ClearTimer(ActiveTimerHandle);
	}
	FTimerDelegate ActiveDelegate;
	ActiveDelegate.BindUObject(this, &UActiveAbilityBase::TriggerActiveEvent);
	GetOuter()->GetWorld()->GetTimerManager().SetTimer(ActiveTimerHandle, ActiveDelegate, BaseFrequency * BaseFrequency,
	                                                   true);
}

void UActiveAbilityBase::TriggerActiveEvent()
{
	UE_LOG(LogTemp, Display, TEXT("TriggerActiveEvent"));
	FTransform SpawnTransform;
	checkf(ProjectileClass, TEXT("ProjectileClass IS NULL"));
	AProjectileBase* Projectile = GetWorld()->SpawnActorDeferred<AProjectileBase>(
		ProjectileClass, SpawnTransform, AbilityComponent->GetOwner(),
		AbilityComponent->SurvivalPlayerCharacter);
	Projectile->SetDamage(BaseDamage * DamageMult);
	Projectile->SetInitialSpeed(2000.f);
	//计算坐标
	SpawnTransform.SetLocation(AbilityComponent->SurvivalPlayerCharacter->GetActorLocation() + AbilityComponent->SurvivalPlayerCharacter->GetActorForwardVector()*100.f);
	//TODO:目前是面朝前发射，后续可以改成EQS检测敌人
	SpawnTransform.SetRotation(AbilityComponent->SurvivalPlayerCharacter->GetActorRotation().Quaternion());
	Projectile->FinishSpawning(SpawnTransform);
}
