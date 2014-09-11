

#include "glbpaintball.h"
#include "PBWeapon.h"
#include "PBCharacter.h"
#include "PBPickUpWeapon.h"


APBPickUpWeapon::APBPickUpWeapon(const class FPostConstructInitializeProperties& PCIP)
	: Super(PCIP)
{

}

bool APBPickUpWeapon::OnPickedUp_Implementation(APBCharacter * Character)
{
	// Create new weapon
	FActorSpawnParameters SpawnInfo;
	SpawnInfo.bNoCollisionFail = true;
	APBWeapon* NewWeapon = GetWorld()->SpawnActor<APBWeapon>(WeaponClass, SpawnInfo);

	if (NewWeapon)
	{
		if (Character->AddWeaponToInventory(NewWeapon))
		{
			return true;
		}
	}
	
	return false;
}
