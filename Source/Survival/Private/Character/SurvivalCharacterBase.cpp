// Fill out your copyright notice in the Description page of Project Settings.


#include "Survival/Public/Character/SurvivalCharacterBase.h"

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

void ASurvivalCharacterBase::OnRep_MaxHealth()
{
	//TODO:更新UI
}

void ASurvivalCharacterBase::OnRep_Health()
{
	//TODO:更新UI
}
