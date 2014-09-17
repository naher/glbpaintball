

#include "glbpaintball.h"
#include "Runtime/AIModule/Classes/Navigation/NavigationComponent.h"
#include "PBEnemy.h"


APBEnemy::APBEnemy(const class FPostConstructInitializeProperties& PCIP)
	: Super(PCIP)
{

}

void APBEnemy::BeginPlay()
{
	Controller = Cast<AAIController>(GetController());

	PointToChase = FVector(0, 0, 0);
}

void APBEnemy::Tick(float DeltaSeconds)
{
	if (EPathFollowingRequestResult::Type::AlreadyAtGoal == 
			Controller->MoveToLocation(PointToChase, 0.2f, true, true, false))
	{
		PointToChase = Controller->NavComponent.Get()->GetRandomPointOnNavMesh().Location;
	}
}