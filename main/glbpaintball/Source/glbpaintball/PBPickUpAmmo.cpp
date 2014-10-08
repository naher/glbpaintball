

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
	if (SoundPickUpItem)
	{
		this->PlaySoundAtLocation(SoundPickUpItem, GetActorLocation(), 0.5f, 1.f);
	}

	if (Weapon && (Weapon->GetAmmo() < Weapon->GetMaxAmmo())) {
		Weapon->AddAmmo(AmmoLoad);
		return true;
	}
	
	return false;
}