

#pragma once

#include "PBPickUp.h"
#include "PBPickUpAmmo.generated.h"

/**
 * 
 */
UCLASS()
class GLBPAINTBALL_API APBPickUpAmmo : public APBPickUp
{
	GENERATED_UCLASS_BODY()

	void OnPickedUp(class APBCharacter * character) override;

protected:

	/** how much ammo does it give? */
	UPROPERTY(EditDefaultsOnly, Category = Pickup)
	int32 AmmoLoad;

	/** which weapon gets ammo? */
	UPROPERTY(EditDefaultsOnly, Category = Pickup)
	UClass * WeaponType;
	
};
