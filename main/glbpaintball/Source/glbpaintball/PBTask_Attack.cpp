

#include "glbpaintball.h"
#include "Runtime/AIModule/Classes/AIController.h"
#include "PBTask_Attack.h"

#include "PBEnemy.h"


UPBTask_Attack::UPBTask_Attack(const class FPostConstructInitializeProperties& PCIP)
	: Super(PCIP)
{

}

EBTNodeResult::Type UPBTask_Attack::ExecuteTask(UBehaviorTreeComponent* OwnerComp, uint8* NodeMemory)
{
	AAIController * Controller = OwnerComp ? Cast<AAIController>(OwnerComp->GetOwner()) : nullptr;

	APBEnemy * Enemy = Controller ? Cast<APBEnemy>(Controller->GetCharacter()) : nullptr;

	if (Enemy)
	{
		Enemy->Attack();
	}

	return EBTNodeResult::Succeeded;
}
