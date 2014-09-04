

#include "glbpaintball.h"
#include "PBPickUpAmmo.h"


APBPickUpAmmo::APBPickUpAmmo(const class FPostConstructInitializeProperties& PCIP)
	: Super(PCIP)
{

}

void APBPickUpAmmo::OnPickedUp(APBCharacter * character)
{
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Blue, TEXT("APBPickUpAmmo::OnPickedUp"));
	}
}
