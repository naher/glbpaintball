

#include "glbpaintball.h"
#include "PBHUDView.h"


UPBHUDView::UPBHUDView(const class FPostConstructInitializeProperties& PCIP)
	: Super(PCIP)
{

}

void UPBHUDView::setAmmo(int32 ammo)
{
	OnSetAmmo(ammo);
}

void UPBHUDView::setWeaponIcon(const UTexture2D * icon)
{
	OnSetWeaponIcon(icon);
}

void UPBHUDView::setMaxAmmo(int32 max_ammo)
{
	OnSetMaxAmmo(max_ammo);
}

void UPBHUDView::setHealth(float health)
{
	OnSetHealth(health);
}

void UPBHUDView::releaseWeapon()
{
	OnReleaseWeapon();
}

