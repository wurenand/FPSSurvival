// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ObjectPoolComponent.generated.h"

//TODO:将对象池支持动态容量改变
class APoolActor;
class UObjectPoolProfileDataAsset;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class NPOBJECTPOOL_API UObjectPoolComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UObjectPoolComponent();
	
	/**
	 * 尝试请求Actor，在外部需要调用SetEnableActor true
	 * @return 
	 */
	APoolActor* RequestActorFromPool();

	void ReleaseActorToPool(APoolActor* ActorToRelease);

	//在拥有者BeginPlay的时候调用，确保World存在
	void InitializeObjectPool(UWorld* InWorld,AActor* InPoolActorOwner = nullptr);


	UPROPERTY(EditAnywhere,Category = "Info")
	TObjectPtr<UObjectPoolProfileDataAsset> PoolData;
protected:
	APoolActor* SpawnNewActor();
	
	UPROPERTY()
	TMap<TObjectPtr<APoolActor>,bool> ObjectMap;
	UPROPERTY()
	TObjectPtr<UWorld> World = nullptr;
	UPROPERTY()
	TObjectPtr<AActor> PoolActorOwner = nullptr;

};
