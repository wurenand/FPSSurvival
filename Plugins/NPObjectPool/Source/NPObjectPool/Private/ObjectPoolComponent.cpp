#include "ObjectPoolComponent.h"

#include "ObjectPoolInterface.h"
#include "ObjectPoolProfileDataAsset.h"

UObjectPoolComponent::UObjectPoolComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

AActor* UObjectPoolComponent::RequestActorFromPool()
{
	AActor* ReturnActor = nullptr;
	for (auto ActorPair : ObjectMap)
	{
		if (!ActorPair.Value)
		{
			ActorPair.Value = true;
			ReturnActor = ActorPair.Key;
		}
	}
	if (ReturnActor == nullptr)
	{
		ReturnActor = SpawnNewActor();
	}
	if (IObjectPoolInterface* PoolInterface = Cast<IObjectPoolInterface>(ReturnActor))
	{
		PoolInterface->EnableActor();
	}
	return ReturnActor;
}

void UObjectPoolComponent::ReleaseActorToPool(AActor* ActorToRelease)
{
	if (ObjectMap.Contains(ActorToRelease))
	{
		if (IObjectPoolInterface* PoolInterface = Cast<IObjectPoolInterface>(ActorToRelease))
		{
			PoolInterface->DisableActor();
		}
		ObjectMap[ActorToRelease] = false;
	}
	else
	{
		ActorToRelease->Destroy();
	}
}


void UObjectPoolComponent::InitializeObjectPool(const FWorldContext* WorldContext,
                                                UObjectPoolProfileDataAsset* DataAsset)
{
	World = WorldContext->World();
	PoolData = DataAsset;
	for (int i = 0; i < DataAsset->InitialObjectCount; i++)
	{
		SpawnNewActor();
	}
}

AActor* UObjectPoolComponent::SpawnNewActor()
{
	AActor* NewActor = World->SpawnActorDeferred<AActor>(PoolData->PoolObjectClass, FTransform());
	if (IObjectPoolInterface* PoolInterface = Cast<IObjectPoolInterface>(NewActor))
	{
		PoolInterface->DisableActor();
	}
	if (ObjectMap.Num() < PoolData->MaxObjectCount)
	{
		ObjectMap.Add(NewActor);
		ObjectMap[NewActor] = false;
	}
	NewActor->FinishSpawning(FTransform());
	return NewActor;
}