

#include "glbpaintball.h"
#include "PBCharacter.h"
#include "PBPickUpEnergy.h"


APBPickUpEnergy::APBPickUpEnergy(const class FPostConstructInitializeProperties& PCIP)
	: Super(PCIP)
{

}

bool APBPickUpEnergy::OnPickedUp_Implementation(APBCharacter * Character)
{
	Character->RechargeEnergy(Energy);
	return true;
}

