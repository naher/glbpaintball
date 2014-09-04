

#include "glbpaintball.h"
#include "PBWeapon.h"
#include "PBCharacter.h"
#include "PBPickUpAmmo.h"


APBPickUpAmmo::APBPickUpAmmo(const class FPostConstructInitializeProperties& PCIP)
	: Super(PCIP)
{

}

void APBPickUpAmmo::OnPickedUp_Implementation(APBCharacter * Character)
{
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Blue, TEXT("APBPickUpAmmo::OnPickedUp"));
	}

	APBWeapon * Weapon = Character->GetWeapon(WeaponClass);

	if (Weapon) {
		Weapon->AddAmmo(AmmoLoad);
	}
}