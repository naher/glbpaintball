

#include "glbpaintball.h"
#include "PBService_UpdateStatus.h"

#include "Runtime/AIModule/Classes/BehaviorTree/BlackboardComponent.h"
#include "PBEnemy.h"

UPBService_UpdateStatus::UPBService_UpdateStatus(const class FPostConstructInitializeProperties& PCIP)
	: Super(PCIP)
{

}

void UPBService_UpdateStatus::TickNode(UBehaviorTreeComponent * OwnerComp, uint8 * NodeMemory, float DeltaSeconds)
{
	UBlackboardComponent * Blackboard = OwnerComp->GetBlackboardComponent();

	uint8 BlackboardKeyID = Blackboard->GetKeyID("Status");

	AAIController * Controller = OwnerComp ? Cast<AAIController>(OwnerComp->GetOwner()) : nullptr;

	APBEnemy * Enemy = Cast<APBEnemy>(Controller->GetPawn());

	Blackboard->SetValueAsEnum(BlackboardKeyID, Enemy->GetStatus());
}
