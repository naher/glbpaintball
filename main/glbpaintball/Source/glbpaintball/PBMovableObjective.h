

#pragma once

#include "PBObjective.h"
#include "PBMovableObjective.generated.h"

/**
 * 
 */
UCLASS()
class GLBPAINTBALL_API APBMovableObjective : public APBObjective
{
	GENERATED_UCLASS_BODY()

	UFUNCTION()
	virtual void Tick(float DeltaSeconds) override;

	virtual void BeginPlay() override;

protected:

	/** Sets the next target point to go to */
	virtual void SetNextTarget();

	/** Retrieves the next location to go to */
	virtual FVector GetNextPointLocation();

	/** Speed */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Objective)
	float PixelsPerSecond;

	// Time transcurred in current travel
	float CurrentTravelTime;

	// Total time needed to reach current target
	float TotalTravelTime;

	// Travel Length in Pixels
	float TravelLength;

	// Last point visited and next point to visit
	FVector vLastPointLocation, vNextPointLocation;
	
};
