

#include "FPSProject.h"
#include "FPSMovableObjective.h"


AFPSMovableObjective::AFPSMovableObjective(const class FPostConstructInitializeProperties& PCIP)
	: Super(PCIP)
{
	CurrentTravelTime = 0;

	PrimaryActorTick.bCanEverTick = true;
}

void AFPSMovableObjective::BeginPlay()
{
	SetNextTarget();
}

void AFPSMovableObjective::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	CurrentTravelTime += DeltaSeconds;

	float alpha = CurrentTravelTime / TotalTravelTime;

	FVector newPos = FMath::Lerp(vLastPointLocation,
								 vNextPointLocation, alpha);

	if (CurrentTravelTime >= TotalTravelTime)
	{
		SetNextTarget();
	}

	SetActorLocation(newPos);
}

void AFPSMovableObjective::SetNextTarget()
{
	// Set current travel time to 0
	CurrentTravelTime = 0;

	// Update point locations for path calculation
	vLastPointLocation = vNextPointLocation;
	vNextPointLocation = GetNextPointLocation();

	// Travel length = distance between current target and next target
	TravelLength = FVector::Dist(vLastPointLocation,
		vNextPointLocation);

	TotalTravelTime = TravelLength / PixelsPerSecond;

}

FVector AFPSMovableObjective::GetNextPointLocation()
{
	return FVector(0, 0, 0);
}