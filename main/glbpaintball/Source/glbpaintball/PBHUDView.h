

#pragma once

#include "PBEventController.h"
#include "Blueprint/UserWidget.h"
#include "PBHUDView.generated.h"

/**
 * 
 */
UCLASS()
class GLBPAINTBALL_API UPBHUDView : public UUserWidget, public IPBEventController
{
	GENERATED_UCLASS_BODY()

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = Events)
	void OnSetAmmo(int32 amountAmmo);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = Events)
	void OnSetWeaponIcon(const UTexture2D * icon);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = Events)
	void OnSetMaxAmmo(int32 max_Ammo);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = Events)
	void OnSetHealth(int32 health);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = Events)
	void OnSetEnergy(float _energy);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = Events)
	void OnReleaseWeapon();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = Events)
	void OnAddWeaponInventary( const UTexture2D * icon, int32 key);

public:
	virtual void setAmmo(int32 amountAmmo) override;
	virtual void setWeaponIcon(const UTexture2D * icon) override;
	virtual void setMaxAmmo(int32 max_ammo) override;
	virtual void setHealth(float health) override;
	virtual void setBarEnergy(float benergy) override;
	virtual void releaseWeapon() override;
	virtual void setWeaponInventary(const UTexture2D *icon, int32 key);
};
 