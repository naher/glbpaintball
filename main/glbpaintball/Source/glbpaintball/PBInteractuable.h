

#pragma once
#include "GameFramework/Actor.h"
#include "PBInteractuable.generated.h"

/**
*
*/
UCLASS(abstract)
class APBInteractuable : public AActor
{
	GENERATED_UCLASS_BODY()

public:
	virtual void SetEnabled(bool enable);

};

