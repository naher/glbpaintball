

#pragma once

#include "GameFramework/Actor.h"
#include "PBOnHitEffectsManager.generated.h"

/**
 * 
 */
UCLASS(NotPlaceable, HideCategories = (Info, Rendering, MovementReplication, Replication, Actor))
class GLBPAINTBALL_API APBOnHitEffectsManager : public AActor
{
	GENERATED_UCLASS_BODY()

	void BeginPlay() override;

	void NotifyHit();

private:
	void SetScreenToDefaultScale();
	
	APlayerCameraManager * PlayerCameraManager;

	class APBCharacter * Character;
	
	UCameraComponent * PlayerCamera;

	FVector DefaultScale, OnHitScale;
	
};
