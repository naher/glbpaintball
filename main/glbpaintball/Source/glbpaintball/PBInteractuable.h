

#pragma once
#include "PBInteractuable.generated.h"

/**
*
*/
UINTERFACE(MinimalAPI)
class UPBInteractuable : public UInterface
{
	GENERATED_UINTERFACE_BODY()
};

class IPBInteractuable
{
	GENERATED_IINTERFACE_BODY()
public:
	virtual void SetEnabled(bool enable);

};

