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
	virtual void DisableActor() = 0;
	virtual void EnableActor() = 0;
	
};
