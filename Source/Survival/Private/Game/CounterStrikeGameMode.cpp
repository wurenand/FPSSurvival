// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/CounterStrikeGameMode.h"

#include "Actor/TeamPlayerStart.h"
#include "Character/SurvivalPlayerCharacter.h"
#include "Game/CounterStrikeGameState.h"
#include "Kismet/GameplayStatics.h"
#include "Player/SurvivalPlayerState.h"

void ACounterStrikeGameMode::PostLogin(APlayerController* NewPlayer)
{
	//这里要在PostLogin之前调用，确保在RestartPlayer之前就找到所有的PlayerStart
	UGameplayStatics::GetAllActorsOfClass(this, ATeamPlayerStart::StaticClass(), PlayerStarts);
	Super::PostLogin(NewPlayer);
}

void ACounterStrikeGameMode::RestartPlayer(AController* NewPlayer)
{
	if (PlayerStarts.Num() == 0)
	{
		return;
	}
	//此处为存活玩家的ReSpawn
	if (ASurvivalPlayerCharacter* Character = Cast<ASurvivalPlayerCharacter>(NewPlayer->GetPawn()))
	{
		Character->SetPendingDeath(true);
	}
	if (ASurvivalPlayerState* SurvivalPlayerState = NewPlayer->GetPlayerState<ASurvivalPlayerState>())
	{
		ETeam SpawnTeam = SurvivalPlayerState->GetTeam();
		//如果没有Team 认为是第一次加入，不SpawnCharacter 给一个观战视角
		if (SpawnTeam == ETeam::ETeam_NoTeam)
		{
			return;
		}
		//随机位置
		AActor* SpawnStart = nullptr;
		//注意地图要给所有阵营的PlayerStart，否则会卡死在这里无法Spawn
		while (true)
		{
			SpawnStart = PlayerStarts[FMath::Rand() % PlayerStarts.Num()];
			if (ATeamPlayerStart* TeamPlayerStart = Cast<ATeamPlayerStart>(SpawnStart))
			{
				if (TeamPlayerStart->Team == SpawnTeam)
				{
					break;
				}
			}
		}
		checkf(RedTeamCharacterClass, TEXT("RedTeamCharacterClass Is Null"));
		checkf(BlueTeamCharacterClass, TEXT("BlueTeamCharacterClass Is Null"));
		TSubclassOf<ASurvivalPlayerCharacter> ClassToSpawn = SpawnTeam == ETeam::ETeam_Red
			                                                     ? RedTeamCharacterClass
			                                                     : BlueTeamCharacterClass;
		FActorSpawnParameters SpawnParams;
		SpawnParams.Owner = NewPlayer;
		APawn* SpawnPawn = GetWorld()->SpawnActor<APawn>(ClassToSpawn, SpawnStart->GetActorTransform(), SpawnParams);
		if (SpawnPawn != nullptr)
		{
			NewPlayer->SetPawn(SpawnPawn);
			FinishRestartPlayer(NewPlayer, SpawnStart->GetActorTransform().Rotator());
		}
	}
}

void ACounterStrikeGameMode::PlayerEliminated(ASurvivalCharacterBase* EliminatedCharacter,
	ASurvivalPlayerController* VictimController, ASurvivalPlayerController* AttackerController)
{
	Super::PlayerEliminated(EliminatedCharacter, VictimController, AttackerController);
	EliminatedCharacter->SetPendingDeath();
	if (GetCSGameState()->IsRoundOver(VictimController))
	{
		FTimerDelegate TimerDelegate;
		TimerDelegate.BindUObject(this,&ACounterStrikeGameMode::StartNewRound);
		GetWorld()->GetTimerManager().SetTimer(NewRoundTimerHandle,TimerDelegate,5.0f,false);	
	}
}

void ACounterStrikeGameMode::StartNewRound()
{
	//TODO:这里处理一轮结束的情况
	GetCSGameState()->RedDeadPlayers.Empty();
	GetCSGameState()->BlueDeadPlayers.Empty();
	for (auto PS : GetCSGameState()->RedPlayers)
	{
		RestartPlayer(PS->GetPlayerController());
	}
	for (auto PS : GetCSGameState()->BluePlayers)
	{
		RestartPlayer(PS->GetPlayerController());
	}
}

ACounterStrikeGameState* ACounterStrikeGameMode::GetCSGameState()
{
	if (!CounterStrikeGameState)
	{
		CounterStrikeGameState = GetGameState<ACounterStrikeGameState>();
	}
	return CounterStrikeGameState;
}
