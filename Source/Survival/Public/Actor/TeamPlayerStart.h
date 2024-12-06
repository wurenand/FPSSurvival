// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerStart.h"
#include "TeamPlayerStart.generated.h"

enum class ETeam : uint8;

UCLASS()
class SURVIVAL_API ATeamPlayerStart : public APlayerStart
{
	GENERATED_BODY()

public:
	ETeam Team;
};
