

#pragma once

#include "GameFramework/Actor.h"
#include "FPSObjective.generated.h"

/**
 * 
 */
UCLASS()
class FPSPROJECT_API AFPSObjective : public AActor
{
	GENERATED_UCLASS_BODY()

	// Collision component to be used as root component
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Objective)
	TSubobjectPtr<USphereComponent> BaseCollisionComponent;

	// Static mesh of the objective
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Objective)
	TSubobjectPtr<UStaticMeshComponent> ObjectiveMesh;

protected:
	/** called when projectile hits something */
	UFUNCTION()
	virtual void OnHit(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
	
};
