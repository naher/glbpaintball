

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

	/** Pure virtual function, OnPickedUp_Implementation needs to be implemented in children classes */
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = PickUp)
	bool OnPickedUp(class APBCharacter * character);

protected:

	// Static mesh of the pickup
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = PickUp)
	TSubobjectPtr<UStaticMeshComponent> PickUpMesh;

	/** called upon collision */
	UFUNCTION()
	void OnHit(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
	
};
