
#pragma once

#include "PBWeaponHolder.generated.h"

/**
 * 
 */
UINTERFACE(MinimalAPI)
class UPBWeaponHolder : public UInterface
{
	GENERATED_UINTERFACE_BODY()
};

class IPBWeaponHolder
{
	GENERATED_IINTERFACE_BODY()
public:
	virtual void ApplyWeaponRecoil();

};

