

#include "glbpaintball.h"
#include "Runtime/AIModule/Classes/AIController.h"
#include "Runtime/AIModule/Classes/Navigation/NavigationComponent.h"
#include "PBTask_PatrolVolume.h"

#include "PBEnemy.h"

UPBTask_PatrolVolume::UPBTask_PatrolVolume(const class FPostConstructInitializeProperties& PCIP)
	: Super(PCIP)
{

}

EBTNodeResult::Type UPBTask_PatrolVolume::ExecuteTask(UBehaviorTreeComponent* OwnerComp, 
													  uint8* NodeMemory)
{
	AAIController * Controller = OwnerComp ? Cast<AAIController>(OwnerComp->GetOwner()) : nullptr;

	APBEnemy * Enemy = Controller ? Cast<APBEnemy>(Controller->GetCharacter()) : nullptr;

	if (!Controller)
	{
		return EBTNodeResult::Failed;
	}

	if (EPathFollowingStatus::Idle == Controller->GetMoveStatus())
	{
		FNavLocation RandomLocation;
		Controller->NavComponent.Get()->GetNavData()->GetRandomPointInRadius(Enemy->GetInitialLocation(), Enemy->GetPatrolRadius(), RandomLocation);
		Controller->MoveToLocation(RandomLocation.Location, 0.2f, true, true, false);
	}

	return EBTNodeResult::Succeeded;
}