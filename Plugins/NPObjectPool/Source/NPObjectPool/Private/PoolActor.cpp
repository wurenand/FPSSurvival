// Fill out your copyright notice in the Description page of Project Settings.


#include "PoolActor.h"

#include "ObjectPoolComponent.h"
#include "Net/UnrealNetwork.h"

APoolActor::APoolActor()
{
	bReplicates = true;
}

void APoolActor::SetEnableActor(bool bInIsEnable)
{
	bIsEnable = bInIsEnable;
	OnRep_bIsEnable();
}

void APoolActor::PoolDestroy()
{
	if (bUsePool && PoolComponent != nullptr)
	{
		PoolComponent->ReleaseActorToPool(this);
	}
	else
	{
		Destroy();
	}
}

void APoolActor::Mult_SetActorTransform_Implementation(FTransform Transform)
{
	SetActorTransform(Transform);
}

void APoolActor::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(APoolActor, bIsEnable)
	DOREPLIFETIME(APoolActor, bUsePool)
}

void APoolActor::Mult_PoolActorBeginPlay_Implementation()
{
}

void APoolActor::BeginPlay()
{
	Super::BeginPlay();
	if (!bUsePool)
	{
		Mult_PoolActorBeginPlay_Implementation(); //如果不使用Pool
	}
}

void APoolActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (bIsEnable && bUseLifeSpan)
	{
		PoolLifeSpanRemain -= DeltaTime;
		if (PoolLifeSpanRemain <= 0)
		{
			PoolDestroy();
		}
	}
}

void APoolActor::OnRep_bIsEnable()
{
	if (!bUsePool)
	{
		return;
	}
	PoolLifeSpanRemain = PoolLifeSpan;
	SetActorEnableCollision(bIsEnable);
	SetActorTickEnabled(bIsEnable);
	SetActorHiddenInGame(!bIsEnable);
	NetUpdateFrequency = bIsEnable ? 100 : 2;
}
