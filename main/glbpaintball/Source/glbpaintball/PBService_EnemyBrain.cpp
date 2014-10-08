

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

void UPBService_EnemyBrain::InitializeFromAsset(UBehaviorTree * Asset)
{
	Super::InitializeFromAsset(Asset);
}

void UPBService_EnemyBrain::TickNode(UBehaviorTreeComponent * OwnerComp, uint8 * NodeMemory, float DeltaSeconds)
{
	Character = Cast<APBCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));

	UBlackboardComponent * Blackboard = OwnerComp->GetBlackboardComponent();

	uint8 BlackboardKeyID = Blackboard->GetKeyID("Status");

	AAIController * Controller = OwnerComp ? Cast<AAIController>(OwnerComp->GetOwner()) : nullptr;

	if (!Controller)
	{
		return;
	}

	float Distance= FVector::Dist(Character->GetActorLocation(), Controller->GetPawn()->GetActorLocation());

	if (Distance > Blackboard->GetValueAsInt(BlackboardKeyID))
	{
		Blackboard->SetValueAsEnum(BlackboardKeyID, 0);
	}
	else
	{
		Blackboard->SetValueAsEnum(BlackboardKeyID, 1);
	}
}
