

#include "glbpaintball.h"
#include "PBWeapon.h"
#include "PBCharacter.h"
#include "PBPickUpMaxAmmo.h"


APBPickUpMaxAmmo::APBPickUpMaxAmmo(const class FPostConstructInitializeProperties& PCIP)
	: Super(PCIP)
{

}

bool APBPickUpMaxAmmo::OnPickedUp_Implementation(APBCharacter * Character)
{
	APBWeapon * Weapon = Character->GetWeapon(WeaponClass);

	if (Weapon)
	{
		Weapon->SetMaxAmmo(Weapon->GetMaxAmmo() + MaxAmmoInc);
		return true;
	}

	return false;
}
