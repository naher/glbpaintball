

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
		//Play Sound
		if (SoundPickUpItem)
		{
			this->PlaySoundAtLocation(SoundPickUpItem, GetActorLocation(), 1.f, 1.f);
		}

		if (Character->AddWeaponToInventory(NewWeapon))
		{
			return true;
		}
	}
	
	return false;
}
