// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "TotalGameModeBase.generated.h"

class UObjectPoolProfileDataAsset;
class UObjectPoolComponent;
class ATeamPlayerStart;
class ASurvivalPlayerController;
class ASurvivalCharacterBase;
/**
 * 
 */
UCLASS()
class SURVIVAL_API ATotalGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	//其实这些好像都不需要...
	virtual void PostLogin(APlayerController* NewPlayer) override;
	virtual void Logout(AController* Exiting) override;
	//根据不同的GameMode自定义效果
	virtual void PlayerEliminated(ASurvivalCharacterBase* EliminatedCharacter,
	                              ASurvivalPlayerController* VictimController,
	                              ASurvivalPlayerController* AttackerController);
	virtual void BeginPlay() override;

	//GameMode中ActorPool所在位置
	UPROPERTY()
	TMap<UClass*, TObjectPtr<UObjectPoolComponent>> ActorPools;
protected:
	//在PostLogin之后就更新一次，这时候在RestartPlayer调用之前 当然是按需的(为什么Server端Post)
	UPROPERTY(EditAnywhere)
	TArray<AActor*> PlayerStarts;
	UPROPERTY()
	TArray<APlayerController*> ConnectedPlayers;

	UPROPERTY(EditAnywhere, Category = "Pools")
	TArray<TObjectPtr<UObjectPoolProfileDataAsset>> PoolData;
};
