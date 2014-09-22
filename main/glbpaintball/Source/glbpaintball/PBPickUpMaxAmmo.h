

#pragma once

#include "PBPickUp.h"
#include "PBPickUpMaxAmmo.generated.h"

/**
 * 
 */
UCLASS()
class GLBPAINTBALL_API APBPickUpMaxAmmo : public APBPickUp
{
	GENERATED_UCLASS_BODY()

protected:

	/** Max Ammo increase */
	UPROPERTY(EditAnywhere, Category = Pickup)
	int32 MaxAmmoInc;

	/** which weapon gets more max ammo? */
	UPROPERTY(EditAnywhere, Category = Pickup)
	UClass * WeaponClass;

	virtual bool OnPickedUp_Implementation(APBCharacter * Character) override;
	
};
