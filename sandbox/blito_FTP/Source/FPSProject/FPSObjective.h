

#pragma once

#include "GameFramework/Actor.h"
#include "FPSObjective.generated.h"

/**
 * 
 */
UCLASS(Abstract)
class FPSPROJECT_API AFPSObjective : public AActor
{
	GENERATED_UCLASS_BODY()
	
protected:

	// Collision component to be used as root component
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Objective)
	TSubobjectPtr<USphereComponent> BaseCollisionComponent;

	// Static mesh of the objective
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Objective)
	TSubobjectPtr<UStaticMeshComponent> ObjectiveMesh;

	/** called when projectile hits something */
	UFUNCTION(BlueprintImplementableEvent, Category = Objective)
	virtual void OnHit(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
	
};