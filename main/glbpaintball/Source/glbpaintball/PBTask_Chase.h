

#pragma once

#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "PBTask_Chase.generated.h"

/**
 * 
 */
UCLASS()
class GLBPAINTBALL_API UPBTask_Chase : public UBTTask_BlackboardBase
{
	GENERATED_UCLASS_BODY()

	EBTNodeResult::Type ExecuteTask(class UBehaviorTreeComponent* OwnerComp, uint8* NodeMemory) override;	
};
