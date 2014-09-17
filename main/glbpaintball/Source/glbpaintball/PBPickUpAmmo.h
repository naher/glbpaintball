

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

protected:

	/** how much ammo does it give? */
	UPROPERTY(EditAnywhere, Category = Pickup)
	int32 AmmoLoad;

	/** which weapon gets ammo? */
	UPROPERTY(EditAnywhere, Category = Pickup)
	TSubclassOf<class APBWeapon> WeaponClass;

	virtual bool OnPickedUp_Implementation(APBCharacter * Character) override;
	
};
