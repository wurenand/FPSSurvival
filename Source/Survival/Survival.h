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
};