

#pragma once

#include "BehaviorTree/Services/BTService_BlackboardBase.h"
#include "PBService_EnemyBrain.generated.h"

/**
 * 
 */
UCLASS()
class GLBPAINTBALL_API UPBService_EnemyBrain : public UBTService_BlackboardBase
{
	GENERATED_UCLASS_BODY()

	void TickNode(UBehaviorTreeComponent * OwnerComp, uint8 * NodeMemory, float DeltaSeconds) override;

	FBlackboardKeySelector Status;
	
};
