

#include "glbpaintball.h"
#include "PBEventController.h"


UPBEventController::UPBEventController(const class FPostConstructInitializeProperties& PCIP)
	: Super(PCIP)
{

}

void IPBEventController::setAmmo(int32 ammo)
{}

void IPBEventController::setWeaponIcon(const UTexture2D * icon)
{}

void IPBEventController::setMaxAmmo(int32 max_ammo)
{}

void IPBEventController::setHealth(float health)
{}

void IPBEventController::setBarEnergy(float benergy)
{}

void IPBEventController::setWeaponInventary(const UTexture2D *icon, int32 key)
{}

void IPBEventController::releaseWeapon()
{}
