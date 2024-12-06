// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/TotalGameStateBase.h"

#include "Net/UnrealNetwork.h"

void ATotalGameStateBase::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(ATotalGameStateBase,ConnectedPlayerStates);
}
