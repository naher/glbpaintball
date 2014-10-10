

#pragma once

#include "BehaviorTree/Services/BTService_BlackboardBase.h"
#include "PBService_UpdateStatus.generated.h"

/**
 * 
 */
UCLASS()
class GLBPAINTBALL_API UPBService_UpdateStatus : public UBTService_BlackboardBase
{
	GENERATED_UCLASS_BODY()

	void TickNode(UBehaviorTreeComponent * OwnerComp, uint8 * NodeMemory, float DeltaSeconds) override;
	
};
