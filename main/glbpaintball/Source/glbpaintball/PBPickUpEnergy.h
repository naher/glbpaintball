

#pragma once

#include "PBPickUp.h"
#include "PBPickUpEnergy.generated.h"

/**
 * 
 */
UCLASS()
class GLBPAINTBALL_API APBPickUpEnergy : public APBPickUp
{
	GENERATED_UCLASS_BODY()

protected:

	UPROPERTY(EditAnywhere, Category = Pickup)
	float Energy;
	
	virtual bool OnPickedUp_Implementation(APBCharacter * Character) override;
	
};
