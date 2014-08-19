

#pragma once

#include "FPSObjective.h"
#include "FPSMovableObjective.generated.h"

/**
 * 
 */
UCLASS()
class FPSPROJECT_API AFPSMovableObjective : public AFPSObjective
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
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Movement)
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
