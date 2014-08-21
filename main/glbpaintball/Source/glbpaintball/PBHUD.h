

#pragma once

#include "GameFramework/HUD.h"
#include "PBHUD.generated.h"

/**
 * 
 */
UCLASS()
class GLBPAINTBALL_API APBHUD : public AHUD
{
	GENERATED_UCLASS_BODY()

private:
	/** Crosshair asset pointer */
	UTexture2D* CrosshairTex;

	/** Primary draw call for the HUD */
	virtual void DrawHUD() override;
	
};
