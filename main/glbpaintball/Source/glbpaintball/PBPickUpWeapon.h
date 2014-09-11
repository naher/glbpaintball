

#pragma once

#include "PBPickUp.h"
#include "PBPickUpWeapon.generated.h"

/**
 * 
 */
UCLASS()
class GLBPAINTBALL_API APBPickUpWeapon : public APBPickUp
{
	GENERATED_UCLASS_BODY()

protected:

	/** Class of the weapon to be picked up */
	UPROPERTY(EditDefaultsOnly, Category = PickUp)
	TSubclassOf<class APBWeapon> WeaponClass;

	virtual bool OnPickedUp_Implementation(APBCharacter * Character) override;
	
};
