

#include "glbpaintball.h"
#include "PBPickup_Ammo.h"


APBPickup_Ammo::APBPickup_Ammo(const class FPostConstructInitializeProperties& PCIP)
	: Super(PCIP)
{

}


bool APBPickup_Ammo::IsForWeapon(UClass * WeaponClass)
{
	return WeaponType == WeaponClass;
}

int32 APBPickup_Ammo::GetAmmoLoad()
{
	return AmmoLoad;
}