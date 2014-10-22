

#include "glbpaintball.h"
#include "PBSpawnVolume.h"
#include "PBPickUp.h"


APBSpawnVolume::APBSpawnVolume(const class FPostConstructInitializeProperties& PCIP)
	: Super(PCIP)
{
	Volume = PCIP.CreateDefaultSubobject<UBoxComponent>(this, TEXT("WhereToSpawn"));

	RootComponent = Volume;

	SpawnDelayRangeLow = 10.0f;
	SpawnDelayRangeHigh = 20.0f;
}

void APBSpawnVolume::BeginPlay()
{
	GetWorldTimerManager().SetTimer(this, &APBSpawnVolume::SpawnPickUp, GetRandomTimePoint(), false);
}

float APBSpawnVolume::GetRandomTimePoint() const
{
	return FMath::FRandRange(SpawnDelayRangeLow, SpawnDelayRangeHigh);
}

FVector APBSpawnVolume::GetRandomPointInVolume() const
{
	FVector RandomLocation;
	float MinX, MinY, MinZ, MaxX, MaxY, MaxZ;

	FVector Origin, BoxExtent;

	Origin = Volume->Bounds.Origin;
	BoxExtent = Volume->Bounds.BoxExtent;

	MinX = Origin.X - BoxExtent.X / 2.0f;
	MinY = Origin.Y - BoxExtent.Y / 2.0f;
	MinZ = Origin.Z - BoxExtent.Z / 2.0f;
	MaxX = Origin.X + BoxExtent.X / 2.0f;
	MaxY = Origin.Y + BoxExtent.Y / 2.0f;
	MaxZ = Origin.Z + BoxExtent.Z / 2.0f;

	RandomLocation.X = FMath::FRandRange(MinX, MaxX);
	RandomLocation.Y = FMath::FRandRange(MinY, MaxY);
	RandomLocation.Z = FMath::FRandRange(MinZ, MaxZ);

	return RandomLocation;
}

void APBSpawnVolume::SpawnPickUp()
{
	if (WhatToSpawn)
	{
		UWorld * World = GetWorld();

		if (World)
		{
			FActorSpawnParameters SpawnParams;
			SpawnParams.Owner = this;
			SpawnParams.Instigator = Instigator;

			World->SpawnActor<APBPickUp>(WhatToSpawn, GetRandomPointInVolume(), FRotator(), SpawnParams);
		}
	}

	GetWorldTimerManager().SetTimer(this, &APBSpawnVolume::SpawnPickUp, GetRandomTimePoint(), false);
}