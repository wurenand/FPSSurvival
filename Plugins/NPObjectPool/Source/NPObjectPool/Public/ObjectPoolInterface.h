#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"

#include "ObjectPoolInterface.generated.h"

UINTERFACE(MinimalAPI)
class UObjectPoolInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 需要被池化的Actor必须要实现的接口
 */
class NPOBJECTPOOL_API IObjectPoolInterface
{
	GENERATED_BODY()

public:
	//开关Actor 通过Actor的bIsEnable复制变量，同步Server和Client  OnServer
	virtual void SetEnableActor(bool bInIsEnable) = 0;
	//PoolActor的销毁函数，主要就是DisableActor然后归还到Pool OnServer
	virtual void PoolDestroy() = 0;
	//PoolActor的BeginPlay，由使用者在拿到Actor并使用的最后调用 使用NetMult是确保所有实例都能调用BeginPlay
	UFUNCTION(NetMulticast,Reliable)
	virtual void PoolActorBeginPlay();//需要重写PoolActorBeginPlay_Implementation
};
