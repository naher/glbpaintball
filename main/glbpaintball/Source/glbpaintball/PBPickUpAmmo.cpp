

#include "glbpaintball.h"
#include "PBWeapon.h"
#include "PBCharacter.h"
#include "PBPickUpAmmo.h"


APBPickUpAmmo::APBPickUpAmmo(const class FPostConstructInitializeProperties& PCIP)
	: Super(PCIP)
{
}

bool APBPickUpAmmo::OnPickedUp_Implementation(APBCharacter * Character)
{
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Blue, TEXT("APBPickUpAmmo::OnPickedUp"));
	}

	APBWeapon * Weapon = Character->GetWeapon(WeaponClass);

	//Play Sound
	if (AudioComp)
	{
		AudioComp->Activate(true);
		AudioComp->Play(0.0f);
	}

	if (Weapon && (Weapon->GetAmmo() < Weapon->GetMaxAmmo())) {
		Weapon->AddAmmo(AmmoLoad);
		return true;
	}
	
	return false;
}