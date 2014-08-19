

#pragma once

#include "FPSMovableObjective.h"
#include "FPSCycleThroughPointsObjective.generated.h"

/**
 * 
 */
UCLASS()
class FPSPROJECT_API AFPSCycleThroughPointsObjective : public AFPSMovableObjective
{
	GENERATED_UCLASS_BODY()

protected:

	/** List of points to cycle through */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Movement)
	TArray<ATargetPoint*> TargetPoints;

private:

	FVector GetNextPointLocation() override;
	
	// Target Points of interest
	int iLastTargetPoint, iNextTargetPoint;
	
};
