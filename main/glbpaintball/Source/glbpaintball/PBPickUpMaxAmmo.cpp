

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
		//Play Sound
		if (AudioComp)
		{
			AudioComp->Activate(true);
			AudioComp->Play(0.0f);
		}

		Weapon->SetMaxAmmo(Weapon->GetMaxAmmo() + MaxAmmoInc);
		return true;
	}

	return false;
}
