#include "Components/SpawnComponent.h"

#include "Data/SpawnProfileDataAsset.h"
#include "Engine/TargetPoint.h"
#include "Interface/SpawnInterface.h"

USpawnComponent::USpawnComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void USpawnComponent::StartSpawning()
{
	//确保在Server端处理逻辑
	if (GetWorld()->GetAuthGameMode() == nullptr || !SpawnProfile || SpawnProfile->Intervals.Num() == 0)
	{
		return;
	}
	bIsSpawning = true;
	IntervalCounter = 0.f;
	CurrentSpawnParamsCopy = SpawnProfile->Intervals[CurrentIntervalIndex];
	//为区间内的每种类，设定定时器来Spawn
	for (auto& ClassToNum : CurrentSpawnParamsCopy.ClassToCount)
	{
		FTimerHandle TimerHandle;
		FTimerDelegate TimerDelegate;
		TimerDelegate.BindLambda([this,&ClassToNum]()-> void
		{
			int32 RandIndex = FMath::RandRange(0, TargetPoint.Num() - 1);
			const FTransform& SpawnPoint = TargetPoint[RandIndex]->GetActorTransform();
			FActorSpawnParameters SpawnParams;
			SpawnParams.Owner = GetWorld()->GetFirstPlayerController(); //确保有连接，能够正常网络复制
			//SpawnActor
			AActor* NewActor = GetWorld()->SpawnActor(ClassToNum.Key, &SpawnPoint, SpawnParams);
			//设置属性(如果实现了的话)
			if (ISpawnInterface* SpawnInterface = Cast<ISpawnInterface>(NewActor))
			{
				SpawnInterface->SetLevel(CurrentSpawnParamsCopy.Level);
			}
		});
		GetWorld()->GetTimerManager().SetTimer(TimerHandle, TimerDelegate,
		                                       CurrentSpawnParamsCopy.Interval / static_cast<float>(ClassToNum.Value),
		                                       true);
		CurrentIntervalHandles.Add(TimerHandle); //Copy进去了，不用担心生命周期问题
	}
}

void USpawnComponent::EndSpawningAll()
{
	bIsSpawning = false;
	for (auto& Handle : CurrentIntervalHandles)
	{
		GetWorld()->GetTimerManager().ClearTimer(Handle);
	}
	CurrentIntervalHandles.Empty();
}

void USpawnComponent::EndSpawningInterval()
{
	EndSpawningAll();
	//继续下一个区间，或重复最后的区间
	if (CurrentIntervalIndex + 1 < SpawnProfile->Intervals.Num())
	{
		CurrentIntervalIndex++;
	}
	StartSpawning();
}

void USpawnComponent::TickComponent(float DeltaTime, enum ELevelTick TickType,
                                    FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	if (bIsSpawning)
	{
		IntervalCounter += DeltaTime;
		//区间计时满就Stop
		if (IntervalCounter >= CurrentSpawnParamsCopy.Interval)
		{
			EndSpawningInterval();
		}
	}
}
