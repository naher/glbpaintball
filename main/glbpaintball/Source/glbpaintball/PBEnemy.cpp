

#include "glbpaintball.h"
#include "Runtime/AIModule/Classes/Navigation/NavigationComponent.h"
#include "PBEnemy.h"

#include <sstream>

APBEnemy::APBEnemy(const class FPostConstructInitializeProperties& PCIP)
	: Super(PCIP)
{

}

void APBEnemy::BeginPlay()
{
	Controller = Cast<AAIController>(GetController());

	SetNextTarget();

}

void APBEnemy::Tick(float DeltaSeconds)
{
	if (EPathFollowingRequestResult::Type::AlreadyAtGoal == 
			Controller->MoveToLocation(PointToChase, 0.2f, true, true, false))
	{
		SetNextTarget();
	}
}

void APBEnemy::SetNextTarget()
{
	PointToChase = Controller->NavComponent.Get()->GetRandomPointOnNavMesh().Location;
}