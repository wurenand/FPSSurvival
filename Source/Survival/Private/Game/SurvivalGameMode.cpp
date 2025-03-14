// Fill out your copyright notice in the Description page of Project Settings.


#include "Survival/Public/Game/SurvivalGameMode.h"

#include "Actor/CollisionInteract/XPBallActor.h"
#include "Character/SurvivalCharacterBase.h"
#include "Components/SpawnComponent.h"
#include "Game/SurvivalGameState.h"
#include "Player/SurvivalPlayerController.h"

ASurvivalGameMode::ASurvivalGameMode()
{
	XPBallPool = CreateDefaultSubobject<UObjectPoolComponent>(TEXT("XPBallPool"));
	EnemySpawn = CreateDefaultSubobject<USpawnComponent>(TEXT("EnemySpawn"));
}


void ASurvivalGameMode::BeginPlay()
{
	Super::BeginPlay();
	if (XPBallPool->PoolData)
	{
		XPBallPool->InitializeObjectPool(GetWorld(), GetWorld()->GetFirstPlayerController());
	}
	EnemySpawn->StartSpawning();
}


void ASurvivalGameMode::PlayerEliminated(ASurvivalCharacterBase* EliminatedCharacter,
                                         ASurvivalPlayerController* VictimController,
                                         ASurvivalPlayerController* AttackerController)
{
}

void ASurvivalGameMode::EnemyEliminated(ASurvivalCharacterBase* EliminatedCharacter,
                                        ASurvivalPlayerController* AttackerController)
{
	//TODO:Spawn经验球
	if (XPBallPool->PoolData)
	{
		APoolActor* PoolActor = XPBallPool->RequestActorFromPool();
		if (AXPBallActor* XPBall = Cast<AXPBallActor>(PoolActor))
		{
			XPBall->SetXP(10);
			XPBall->SetActorLocation(EliminatedCharacter->GetActorLocation());
		}
		PoolActor->FinishRequesting();
	}
	//DestroyEnemy
	EliminatedCharacter->SetPendingDeath();
	FTimerHandle TimerHandle;
	FTimerDelegate TimerDelegate;
	TimerDelegate.BindLambda([EliminatedCharacter]()-> void
	{
		if (IsValid(EliminatedCharacter))
		{
			EliminatedCharacter->Destroy();
		}
	});
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, TimerDelegate, 2.f, false);
}

void ASurvivalGameMode::LevelUp()
{
	ReadyPlayers.Empty();
	for (auto Player : ConnectedPlayers)
	{
		if (ASurvivalPlayerController* SurvivalPlayerController = Cast<ASurvivalPlayerController>(Player))
		{
			SurvivalPlayerController->CL_HandleLevelUp();
		}
	}
}

void ASurvivalGameMode::PlayerResume(ASurvivalPlayerController* Player)
{
	if (!ReadyPlayers.Contains(Player))
	{
		ReadyPlayers.Add(Player);
	}
	if (ReadyPlayers.Num() == ConnectedPlayers.Num())
	{
		for (auto EachPlayer : ReadyPlayers)
		{
			//TODO:这里后续增加更多升级的逻辑，目前先切换UI
			EachPlayer->CL_ChangeOverlayPage(TEXT("Default"));
		}
		GetSurvivalGameState()->SetAllGamePause(false);
	}
}

ASurvivalGameState* ASurvivalGameMode::GetSurvivalGameState()
{
	if (!SurvivalGameState)
	{
		SurvivalGameState = Cast<ASurvivalGameState>(GameState);
	}
	return SurvivalGameState;
}
