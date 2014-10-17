#pragma once
#include "PBEventController.generated.h"


UINTERFACE(MinimalAPI)
class UPBEventController : public UInterface
{
	GENERATED_UINTERFACE_BODY()
};

class IPBEventController
{
	GENERATED_IINTERFACE_BODY()

	virtual void setAmmo(int32 ammo);
	virtual void setWeaponIcon(const UTexture2D * icon);
	virtual void setMaxAmmo(int32 max_ammo);
	virtual void setHealth(float health);
	virtual void releaseWeapon();
	virtual void setBarEnergy(float benergy);
	virtual void setWeaponInventary(const UTexture2D *icon, int32 key);
};

