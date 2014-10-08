

#pragma once
#include "PBInteractuable.h"
#include "GameFramework/Actor.h"
#include "PBButton.generated.h"

/**
 * 
 */
UCLASS()
class GLBPAINTBALL_API APBButton : public AActor
{
	GENERATED_UCLASS_BODY()

	UPROPERTY(EditDefaultsOnly, Category = Button)
	IPBInteractuable * Target;
	
	
};
