

#include "FPSProject.h"
#include "FPSMovableInVolumeObjective.h"


AFPSMovableInVolumeObjective::AFPSMovableInVolumeObjective(const class FPostConstructInitializeProperties& PCIP)
	: Super(PCIP)
{

}

FVector AFPSMovableInVolumeObjective::GetNextPointLocation()
{
	if (!MovementVolume)
		return FVector(0, 0, 0);

	FVector vRandomLocation;

	float MinX, MinY, MinZ;
	float MaxX, MaxY, MaxZ;

	FVector Origin, BoxExtent;

	Origin = MovementVolume->Bounds.Origin;
	BoxExtent = MovementVolume->Bounds.BoxExtent;

	MinX = Origin.X - BoxExtent.X / 2.f;
	MinY = Origin.Y - BoxExtent.Y / 2.f;
	MinZ = Origin.Z - BoxExtent.Z / 2.f;

	MaxX = Origin.X + BoxExtent.X / 2.f;
	MaxY = Origin.Y + BoxExtent.Y / 2.f;
	MaxZ = Origin.Z + BoxExtent.Z / 2.f;

	vRandomLocation.X = FMath::FRandRange(MinX, MaxX);
	vRandomLocation.Y = FMath::FRandRange(MinY, MaxY);
	vRandomLocation.Z = FMath::FRandRange(MinZ, MaxZ);

	return vRandomLocation;
}

