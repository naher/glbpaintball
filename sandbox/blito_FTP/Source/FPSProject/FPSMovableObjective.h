

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

	/** List of points to cycle through */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Objective)
	TArray<ATargetPoint*> TargetPoints;
	
	/** Speed */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Objective)
	float PixelsPerSecond;

	UFUNCTION()
	virtual void Tick(float DeltaSeconds) override;

	virtual void BeginPlay() override;

private:

	/** Sets the next target point to go to */
	void SetNextTarget();

	// Target Points of interest
	int iLastTargetPoint, iNextTargetPoint;

	// true: start->end, false: start<-end
	bool bIsMovingForward;

	// Time transcurred in current travel
	float CurrentTravelTime;

	// Total time needed to reach current target
	float TotalTravelTime;

	// Travel Length in Pixels
	float TravelLength;

};
