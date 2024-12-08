// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "Player/SurvivalPlayerState.h"
#include "TotalGameStateBase.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnGameStateValueChangedSignature,float,value);

USTRUCT(BlueprintType, Blueprintable)
struct FDataStruct
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	TObjectPtr<UDataTable> WeaponDataTable;
};

/**
 * 
 */
UCLASS()
class SURVIVAL_API ATotalGameStateBase : public AGameStateBase
{
	GENERATED_BODY()
	//下面是关于数据表等..
public:
	FORCEINLINE const FDataStruct& GetDataStruct() { return DataStruct; }

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	//记录当前链接到的所有的PlayerState 用于同步信息给Client  由GameMode负责管理
	UPROPERTY(Replicated , BlueprintReadOnly, Category = "Player")
	TArray<ASurvivalPlayerState*> ConnectedPlayerStates;
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	FDataStruct DataStruct;
};
