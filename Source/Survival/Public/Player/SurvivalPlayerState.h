// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "Survival/Survival.h"
#include "SurvivalPlayerState.generated.h"

class UAbilityComponent;

UCLASS()
class SURVIVAL_API ASurvivalPlayerState : public APlayerState
{
	GENERATED_BODY()

public:
	ASurvivalPlayerState();
	virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;
	
	UAbilityComponent* GetAbilityComponent() const;
	FORCEINLINE ETeam GetTeam() const { return Team; }
	
	//Only Used In CS
	UFUNCTION(Server, Reliable,BlueprintCallable)
	void SRV_SetTeam(ETeam NewTeam);

protected:
	UPROPERTY(VisibleAnywhere,Replicated ,Category = "Ability")
	TObjectPtr<UAbilityComponent> AbilityComponent;

	UPROPERTY(VisibleAnywhere, Replicated, Category = "Team")
	ETeam Team = ETeam::ETeam_NoTeam;
};
