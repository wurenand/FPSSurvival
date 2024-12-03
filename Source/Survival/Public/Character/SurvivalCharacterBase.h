// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "SurvivalCharacterBase.generated.h"

UCLASS()
class SURVIVAL_API ASurvivalCharacterBase : public ACharacter
{
	GENERATED_BODY()

public:
	ASurvivalCharacterBase();

	virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;
	//TODO:用于初始化数值的，包括HP，弹药等 Player与Enemy不同
	virtual void InitializeAttributes();
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, ReplicatedUsing = OnRep_MaxHealth, Category="Health")
	float MaxHealth;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, ReplicatedUsing = OnRep_Health, Category="Health")
	float Health;
	UFUNCTION()
	void OnRep_MaxHealth();
	UFUNCTION()
	void OnRep_Health();
};
