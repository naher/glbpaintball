

#pragma once

#include "GameFramework/HUD.h"

/*#include "Runtime/UMG/Public/UMG.h"
#include "Runtime/UMG/Public/UMGStyle.h"
#include "Runtime/UMG/Public/Slate/SObjectWidget.h"
#include "Runtime/UMG/Public/IUMGModule.h"
#include "Runtime/UMG/Public/Blueprint/UserWidget.h"*/
#include "PBHUDView.h"

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

public:
	//UUserWidget * hud;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = UI)
		UPBHUDView *HUDView;
};
