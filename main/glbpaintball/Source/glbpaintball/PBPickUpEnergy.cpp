

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
	if (AudioComp)
	{
		AudioComp->Activate(true);
		AudioComp->Play(0.0f);
	}

	Character->RechargeEnergy(Energy);
	return true;
}

