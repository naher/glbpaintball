

#include "FPSProject.h"
#include "FPSCycleThroughPointsObjective.h"


AFPSCycleThroughPointsObjective::AFPSCycleThroughPointsObjective(const class FPostConstructInitializeProperties& PCIP)
	: Super(PCIP)
{
	iLastTargetPoint = 0;
	iNextTargetPoint = 0;
}

FVector AFPSCycleThroughPointsObjective::GetNextPointLocation()
{
	// Stand still if we have nowhere to go to
	if (TargetPoints.Num() == 0)
		return GetActorLocation();

	// We arrived to our old NextTargetPoint
	iLastTargetPoint = iNextTargetPoint;

	// find next target point
	iNextTargetPoint = (iLastTargetPoint + 1 < TargetPoints.Num()) ? iLastTargetPoint + 1 : 0;

	return TargetPoints[iNextTargetPoint]->GetActorLocation();
}