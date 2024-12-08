// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/CounterStrikeGameMode.h"

#include "Actor/TeamPlayerStart.h"
#include "Character/SurvivalPlayerCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "Player/SurvivalPlayerState.h"


//TODO:提供玩家选择的功能 UI

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
