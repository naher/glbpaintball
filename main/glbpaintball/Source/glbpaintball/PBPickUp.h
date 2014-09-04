

#pragma once

#include "GameFramework/Actor.h"
#include "PBPickUp.generated.h"

/**
 * 
 */
UCLASS(abstract)
class GLBPAINTBALL_API APBPickUp : public AActor
{
	GENERATED_UCLASS_BODY()

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = PickUp)
	void OnPickedUp(class APBCharacter * character);

protected:

	// Collision component to be used as root component
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = PickUp)
	TSubobjectPtr<USphereComponent> BaseCollisionComponent;

	// Static mesh of the pickup
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = PickUp)
	TSubobjectPtr<UStaticMeshComponent> PickUpMesh;
	
};
