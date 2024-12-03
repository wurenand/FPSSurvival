
#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AbilityComponent.generated.h"


class UAbilityBase;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class SURVIVAL_API UAbilityComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UAbilityComponent();

protected:
	//为什么UObject类型必须要用TObjectPtr才能放在TArray中
	TArray<TObjectPtr<UAbilityBase>> ActiveAbilities;
};
