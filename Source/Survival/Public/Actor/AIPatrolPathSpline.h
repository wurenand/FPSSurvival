// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AIPatrolPathSpline.generated.h"

class USplineComponent;

UCLASS()
class SURVIVAL_API AAIPatrolPathSpline : public AActor
{
	GENERATED_BODY()

public:
	AAIPatrolPathSpline();
	
	//用于AI巡逻的巡逻点使用
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Spline")
	TObjectPtr<USplineComponent> PathSplineComponent;
};
