
#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AbilityComponent.generated.h"


class AWeaponBase;
class UAbilityBase;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class SURVIVAL_API UAbilityComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UAbilityComponent();

	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category="Weapon")
	TSubclassOf<AWeaponBase> WeaponClass;
	
protected:
	//为什么UObject类型必须要用TObjectPtr才能放在TArray中
	TArray<TObjectPtr<UAbilityBase>> ActiveAbilities;

};
