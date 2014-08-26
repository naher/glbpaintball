

#pragma once

#include "PBMovableObjective.h"
#include "PBCycleThroughTargetsObjective.generated.h"

/**
 * 
 */
UCLASS()
class GLBPAINTBALL_API APBCycleThroughTargetsObjective : public APBMovableObjective
{
	GENERATED_UCLASS_BODY()

protected:

	/** List of points to cycle through */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Objective)
	TArray<ATargetPoint*> TargetPoints;

private:

	FVector GetNextPointLocation() override;

	// Target Points of interest
	int iLastTargetPoint, iNextTargetPoint;
	
};
