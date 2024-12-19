// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

//阵营定义
UENUM(BlueprintType)
enum class ETeam : uint8
{
	ETeam_Red UMETA(DisplayName = "Red"),
	ETeam_Blue UMETA(DisplayName = "Blue"),
	ETeam_NoTeam UMETA(DisplayName = "NoTeam"),
	ETeam_Enemy UMETA(DisplayName = "Enemy"),
};

#define ECC_Ability ECollisionChannel::ECC_GameTraceChannel1
#define ECC_PlayerInteract ECollisionChannel::ECC_GameTraceChannel2