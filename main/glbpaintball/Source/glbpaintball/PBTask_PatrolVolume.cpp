

#include "glbpaintball.h"
#include "Runtime/AIModule/Classes/AIController.h"
#include "Runtime/AIModule/Classes/Navigation/NavigationComponent.h"
#include "PBTask_PatrolVolume.h"


UPBTask_PatrolVolume::UPBTask_PatrolVolume(const class FPostConstructInitializeProperties& PCIP)
	: Super(PCIP)
{

}

EBTNodeResult::Type UPBTask_PatrolVolume::ExecuteTask(UBehaviorTreeComponent* OwnerComp, 
													  uint8* NodeMemory)
{
	AAIController * Controller = Cast<AAIController>(OwnerComp->GetOwner());

	if (EPathFollowingRequestResult::Type::AlreadyAtGoal ==
		Controller->MoveToLocation(PointToChase, 0.2f, true, true, false))
	{
		PointToChase = Controller->NavComponent.Get()->GetRandomPointOnNavMesh().Location;
	}

	return EBTNodeResult::Succeeded;
}
