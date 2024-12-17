// Fill out your copyright notice in the Description page of Project Settings.


#include "Library/PoolHelperLibrary.h"

#include "Game/TotalGameModeBase.h"

UObjectPoolComponent* UPoolHelperLibrary::GetPoolFromActorClass(const UObject* WorldContextObject, UClass* ActorClass)
{
	if (ATotalGameModeBase* GameModeBase = Cast<ATotalGameModeBase>(WorldContextObject->GetWorld()->GetAuthGameMode()))
	{
		if (GameModeBase->ActorPools.Contains(ActorClass))
		{
			return GameModeBase->ActorPools[ActorClass];
		}
	}
	return nullptr;
}
