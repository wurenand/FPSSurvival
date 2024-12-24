#include "ObjectPoolComponent.h"
#include "ObjectPoolProfileDataAsset.h"
#include "PoolActor.h"
#include "GameFramework/PlayerState.h"

UObjectPoolComponent::UObjectPoolComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

APoolActor* UObjectPoolComponent::RequestActorFromPool()
{
	APoolActor* ReturnActor = nullptr;
	for (auto& ActorPair : ObjectMap)
	{
		if (!ActorPair.Value)
		{
			ActorPair.Value = true;
			ReturnActor = ActorPair.Key;
			break;
		}
	}
	if (ReturnActor == nullptr)
	{
		ReturnActor = SpawnNewActor();
	}
	//标记为使用，放在这里是为了处理SpawnNewActor中获得的，且新存放在Pool的
	if (ObjectMap.Contains(ReturnActor))
	{
		ObjectMap[ReturnActor] = true;
	}
	ReturnActor->SetEnableActor(true);
	return ReturnActor;
}

void UObjectPoolComponent::ReleaseActorToPool(APoolActor* ActorToRelease)
{
	if (ObjectMap.Contains(ActorToRelease))
	{
		ActorToRelease->SetEnableActor(false);
		ObjectMap[ActorToRelease] = false;
	}
	else
	{
		ActorToRelease->Destroy();
	}
}

void UObjectPoolComponent::InitializeObjectPool(UWorld* InWorld, AActor* InPoolActorOwner)
{
	World = InWorld;
	PoolActorOwner = InPoolActorOwner ? InPoolActorOwner : GetOwner()->GetOwner();
	if (PoolData != nullptr)
	{
		for (int i = 0; i < PoolData->InitialObjectCount; i++)
		{
			SpawnNewActor();
		}
	}
}

APoolActor* UObjectPoolComponent::SpawnNewActor()
{
	FTransform Transform;
	Transform.SetLocation(FVector(0, 0, 1000.f));
	APawn* Instigator = nullptr;
	if (APlayerState* PlayerState = Cast<APlayerState>(GetOuter()))
	{
		Instigator = PlayerState->GetPawn();
	}
	APoolActor* NewActor = World->SpawnActorDeferred<APoolActor>(PoolData->PoolObjectClass, Transform,
	                                                            PoolActorOwner, Instigator);
	if (ObjectMap.Num() < PoolData->MaxObjectCount)
	{
		ObjectMap.Add(NewActor);
		ObjectMap[NewActor] = false;
		//如果Pool还能容纳，则池化
		NewActor->bUsePool = true;
	}
	NewActor->SetEnableActor(false);
	NewActor->SetPoolComponent(this);
	NewActor->FinishSpawning(Transform);
	return NewActor;
}
