

#include "glbpaintball.h"
#include "PBMovableObjective.h"


APBMovableObjective::APBMovableObjective(const class FPostConstructInitializeProperties& PCIP)
	: Super(PCIP)
{
	CurrentTravelTime = 0;

	PrimaryActorTick.bCanEverTick = true;
}

void APBMovableObjective::BeginPlay()
{
	SetNextTarget();
}

void APBMovableObjective::Tick(float DeltaSeconds)
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

void APBMovableObjective::SetNextTarget()
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

FVector APBMovableObjective::GetNextPointLocation()
{
	return FVector(0, 0, 0);
}
