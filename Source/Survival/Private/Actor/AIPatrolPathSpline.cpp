#include "Actor/AIPatrolPathSpline.h"

#include "Components/SplineComponent.h"

AAIPatrolPathSpline::AAIPatrolPathSpline()
{
	PrimaryActorTick.bCanEverTick = false;
	PathSplineComponent = CreateDefaultSubobject<USplineComponent>(TEXT("PathSplineComponent"));
	PathSplineComponent->SetupAttachment(GetRootComponent());
}
