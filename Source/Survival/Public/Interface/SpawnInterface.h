#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "SpawnInterface.generated.h"

UINTERFACE()
class USpawnInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 用于Spawn系统， 根据Level设置数值
 */
class SURVIVAL_API ISpawnInterface
{
	GENERATED_BODY()

public:
	//根据Level设置数值
	virtual void SetLevel(int32 Level) = 0;
};
