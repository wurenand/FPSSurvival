
#pragma once

#include "CoreMinimal.h"
#include "Actor/WeaponBase.h"
#include "Components/ActorComponent.h"
#include "AbilityComponent.generated.h"

struct FAbilityHandle;
class ASurvivalPlayerCharacter;
class ASurvivalPlayerState;
class UWeaponAbility;
class AWeaponBase;
class UAbilityBase;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class SURVIVAL_API UAbilityComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UAbilityComponent();
	virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;

	const FAbilityHandle* IsOwningAbility(FName AbilityName) const;
	
	UPROPERTY()
	TObjectPtr<ASurvivalPlayerCharacter> SurvivalPlayerCharacter;
	
	//~Begin ShootLogic
	float GetShootFrequency();
	float GetShootDamage();
	//~End ShootLogic
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category="Weapon")
	TSubclassOf<AWeaponBase> WeaponClass;
	FWeaponInfo WeaponInfo;

	//给技能升级，如果没有这个技能，则给予 On Server
	void TryLevelUpAbility(FName AbilityName);
	UAbilityBase* GiveAbility(FName AbilityName);
	
	//发生在OnRep_Weapon之后
	//使得Character能够拿到收到所有数值变化 并获取初始值并广播 OnServer
	void BindAllValueDelegatesAndInit();
	
protected:
	//Server
	UPROPERTY()
	TObjectPtr<UWeaponAbility> WeaponAbility;
	//为什么UObject类型必须要用TObjectPtr才能放在TArray中
	UPROPERTY()
	TArray<TObjectPtr<UAbilityBase>> ActiveAbilities;
	//快速查找Ability
	UPROPERTY()
	TMap<FName,TObjectPtr<UAbilityBase>> NameToAbility;

	//同步结构体到Client，Client根据这个知晓当前已经拥有的Ability和Level
	UPROPERTY(ReplicatedUsing = OnRep_AbilityHandles)
	TArray<FAbilityHandle> AbilityHandles;
	UFUNCTION()
	void OnRep_AbilityHandles();
};



