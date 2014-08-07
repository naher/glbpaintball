

#include "FPSProject.h"
#include "FPSMovableObjective.h"


AFPSMovableObjective::AFPSMovableObjective(const class FPostConstructInitializeProperties& PCIP)
	: Super(PCIP)
{
	CurrentTravelTime = 0;
	iLastTargetPoint = 0;
	iNextTargetPoint = 0;
	bIsMovingForward = true;

	PrimaryActorTick.bCanEverTick = true;
}

void AFPSMovableObjective::BeginPlay()
{
	if (TargetPoints.Num() > 1)
	{
		SetNextTarget();
	}
}

void AFPSMovableObjective::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	CurrentTravelTime += DeltaSeconds;

	float alpha = CurrentTravelTime / TotalTravelTime;

	FVector newPos = FMath::Lerp(TargetPoints[iLastTargetPoint]->GetActorLocation(),
								 TargetPoints[iNextTargetPoint]->GetActorLocation(), alpha);

	if (CurrentTravelTime >= TotalTravelTime)
	{
		SetNextTarget();
		//bIsMovingForward = !bIsMovingForward;
	}

	SetActorLocation(newPos);
}

void AFPSMovableObjective::SetNextTarget()
{
	// We arrived to our old NextTargetPoint
	iLastTargetPoint = iNextTargetPoint;

	// find next target point
	iNextTargetPoint = (iLastTargetPoint + 1 < TargetPoints.Num()) ? iLastTargetPoint + 1 : 0;

	// Set current travel time to 0
	CurrentTravelTime = 0;
	
	// Travel length = distance between current target and next target
	TravelLength = FVector::Dist(TargetPoints[iLastTargetPoint]->GetActorLocation(),
								TargetPoints[iNextTargetPoint]->GetActorLocation());

	TotalTravelTime = TravelLength / PixelsPerSecond;
}