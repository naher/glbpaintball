

#include "glbpaintball.h"
#include "Runtime/AIModule/Classes/AIController.h"
#include "Runtime/AIModule/Classes/Navigation/NavigationComponent.h"
#include "PBTask_Chase.h"


UPBTask_Chase::UPBTask_Chase(const class FPostConstructInitializeProperties& PCIP)
	: Super(PCIP)
{

}

EBTNodeResult::Type UPBTask_Chase::ExecuteTask(class UBehaviorTreeComponent* OwnerComp, uint8* NodeMemory)
{
	ACharacter * PlayerCharacter = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	AAIController * Controller = Cast<AAIController>(OwnerComp->GetOwner());

	Controller->MoveToLocation(PlayerCharacter->GetActorLocation(), 0.2f, true, true, false);

	return EBTNodeResult::Succeeded;
}
