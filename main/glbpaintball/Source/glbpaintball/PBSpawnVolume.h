

#pragma once

#include "GameFramework/Actor.h"
#include "PBSpawnVolume.generated.h"

/**
 * 
 */
UCLASS()
class GLBPAINTBALL_API APBSpawnVolume : public AActor
{
	GENERATED_UCLASS_BODY()

	void BeginPlay() override;

protected:

	UPROPERTY(VisibleInstanceOnly, Category = Spawning)
	TSubobjectPtr<UBoxComponent> Volume;

	UPROPERTY(EditAnywhere, Category = Spawning)
	TSubclassOf<class APBPickUp> WhatToSpawn;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Spawning)
	float SpawnDelayRangeLow;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Spawning)
	float SpawnDelayRangeHigh;

private:

	void SpawnPickUp();

	float GetRandomTimePoint() const;

	FVector GetRandomPointInVolume() const;
	
};
