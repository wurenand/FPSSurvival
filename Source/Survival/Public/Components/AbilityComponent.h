
#pragma once

#include "CoreMinimal.h"
#include "Actor/WeaponBase.h"
#include "Components/ActorComponent.h"
#include "AbilityComponent.generated.h"

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

	UPROPERTY()
	TObjectPtr<ASurvivalPlayerCharacter> SurvivalPlayerCharacter;
	UPROPERTY(Replicated)
	TObjectPtr<ASurvivalPlayerState> OwnerPlayerState;
	
	//~Begin ShootLogic
	float GetShootFrequency();
	float GetShootDamage();
	//~End ShootLogic
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category="Weapon")
	TSubclassOf<AWeaponBase> WeaponClass;
	FWeaponInfo WeaponInfo;

	//给技能升级，如果没有这个技能，则给予 On Server
	void TryLevelUpAbility(FName AbilityName);

	UFUNCTION(NetMulticast,Reliable)
	void Mult_GiveAbility(FName AbilityName,TSubclassOf<UAbilityBase> AbilityClass);
	
	//发生在OnRep_Weapon之后
	//使得Character能够拿到收到所有数值变化 并获取初始值并广播 OnServer
	void BindAllValueDelegatesAndInit();

	
protected:
	UPROPERTY(Replicated)
	TObjectPtr<UWeaponAbility> WeaponAbility;
	//为什么UObject类型必须要用TObjectPtr才能放在TArray中
	UPROPERTY(Replicated)
	TArray<TObjectPtr<UAbilityBase>> ActiveAbilities;
};


