

#include "glbpaintball.h"
#include "PBCharacter.h"
#include "PBPickUpEnergy.h"


APBPickUpEnergy::APBPickUpEnergy(const class FPostConstructInitializeProperties& PCIP)
	: Super(PCIP)
{
}

bool APBPickUpEnergy::OnPickedUp_Implementation(APBCharacter * Character)
{
	//Play Sound
	if (SoundPickUpItem)
	{
		this->PlaySoundAtLocation(SoundPickUpItem, GetActorLocation(), 1.f, 1.f);
	}

	Character->RechargeEnergy(Energy);
	return true;
}

