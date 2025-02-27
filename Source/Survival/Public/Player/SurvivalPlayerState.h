// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "ObjectPoolComponent.h"
#include "GameFramework/PlayerState.h"
#include "Survival/Survival.h"
#include "SurvivalPlayerState.generated.h"

class USurvivalAbilitySystemComponent;
class USurvivalAttributeSet;
class UAbilityComponent;

UCLASS()
class SURVIVAL_API ASurvivalPlayerState : public APlayerState, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	ASurvivalPlayerState();
	virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;

	//GAS
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	USurvivalAttributeSet* GetSurvivalAttributeSet() const;
	UObjectPoolComponent* GetPoolComponent(UClass* PoolActorClass) const;
	FORCEINLINE ETeam GetTeam() const { return Team; }

	//Only Used In CS
	UFUNCTION(Server, Reliable, BlueprintCallable)
	void SRV_SetTeam(ETeam NewTeam);

	virtual void BeginPlay() override;

protected:
	UPROPERTY(VisibleAnywhere, Category = "GAS")
	TObjectPtr<USurvivalAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY(VisibleAnywhere, Category="GAS")
	TObjectPtr<USurvivalAttributeSet> AttributeSet;
	//用来标注ASC是否是第一次初始化，用来授予技能
	bool bAbilitySystemInitialized = false;

	UPROPERTY(EditAnywhere, Category = "Pool")
	TObjectPtr<UObjectPoolComponent> PoolComponent;

	UPROPERTY(VisibleAnywhere, Replicated, Category = "Team")
	ETeam Team = ETeam::ETeam_NoTeam;
};
