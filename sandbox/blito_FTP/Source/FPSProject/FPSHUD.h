

#pragma once

#include "GameFramework/HUD.h"
#include "FPSHUD.generated.h"

/**
 * 
 */
UCLASS()
class FPSPROJECT_API AFPSHUD : public AHUD
{
	GENERATED_UCLASS_BODY()

private:
	/** Crosshair asset pointer */
	UTexture2D* CrosshairTex;
	
	/** Primary draw call for the HUD */
	virtual void DrawHUD() override;
};
