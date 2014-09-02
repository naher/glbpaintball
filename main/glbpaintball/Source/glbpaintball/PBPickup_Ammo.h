

#pragma once

#include "PBObjective.h"
#include "PBPickup_Ammo.generated.h"

/**
 * 
 */
UCLASS()
class GLBPAINTBALL_API APBPickup_Ammo : public APBObjective
{
	GENERATED_UCLASS_BODY()

	bool IsForWeapon(UClass* WeaponClass);

	int32 GetAmmoLoad();

protected:

	/** how much ammo does it give? */
	UPROPERTY(EditDefaultsOnly, Category = Pickup)
	int32 AmmoLoad;

	/** which weapon gets ammo? */
	UPROPERTY(EditDefaultsOnly, Category = Pickup)
	UClass * WeaponType;
	
};
