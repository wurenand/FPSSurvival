// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "SurvivalGameState.generated.h"

USTRUCT(BlueprintType, Blueprintable)
struct FDataStruct
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	TObjectPtr<UDataTable> WeaponDataTable;
};

/**
 * 
 */
UCLASS()
class SURVIVAL_API ASurvivalGameState : public AGameStateBase
{
	GENERATED_BODY()

	//下面是关于数据表等..
public:
	FORCEINLINE const FDataStruct& GetDataStruct() { return DataStruct; };

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	FDataStruct DataStruct;
};
