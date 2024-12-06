
#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "CombatInterface.generated.h"

enum class ETeam : uint8;

UINTERFACE()
class UCombatInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 处理与战斗相关的逻辑接口，如获取Team，ApplyDamage等
 */
class SURVIVAL_API ICombatInterface
{
	GENERATED_BODY()

public:
	//分别由Player和Enemy自己实现
	virtual ETeam GetCharacterTeam() = 0;
};
