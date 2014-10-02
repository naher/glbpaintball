

#include "glbpaintball.h"
#include "PBCharacter.h"
#include "PBService_EnemyBrain.h"

#include "Runtime/AIModule/Classes/BehaviorTree/BlackboardComponent.h"
#include "Runtime/AIModule/Classes/AIController.h"
#include "Runtime/AIModule/Classes/Navigation/NavigationComponent.h"


UPBService_EnemyBrain::UPBService_EnemyBrain(const class FPostConstructInitializeProperties& PCIP)
	: Super(PCIP)
{

}

void UPBService_EnemyBrain::TickNode(UBehaviorTreeComponent * OwnerComp, uint8 * NodeMemory, float DeltaSeconds)
{
	APBCharacter * Character = Cast<APBCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));

	UBlackboardComponent * Blackboard = OwnerComp->GetBlackboardComponent();

	uint8 BlackboardKeyID = Blackboard->GetKeyID("Status");

	AAIController * Controller = Cast<AAIController>(OwnerComp->GetOwner());	

	float dist = FVector::Dist(Character->GetActorLocation(), Controller->GetPawn()->GetActorLocation());

	if (dist > 150.0f)
	{
		Blackboard->SetValueAsEnum(BlackboardKeyID, 0);
	}
	else
	{
		Blackboard->SetValueAsEnum(BlackboardKeyID, 1);
	}
}
