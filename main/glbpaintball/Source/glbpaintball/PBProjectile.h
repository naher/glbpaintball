

#pragma once

#include "GameFramework/Actor.h"
#include "PBProjectile.generated.h"

/**
 * 
 */
UCLASS()
class GLBPAINTBALL_API APBProjectile : public AActor
{
	GENERATED_UCLASS_BODY()

	/** Sphere collision component */
	UPROPERTY(VisibleDefaultsOnly, Category = Projectile)
	TSubobjectPtr<USphereComponent> CollisionComp;

	/** Projectile movement component */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Movement)
	TSubobjectPtr<class UProjectileMovementComponent> ProjectileMovement;

	/** inits velocity of the projectile in the shoot direction */
	void InitVelocity(const FVector& ShootDirection);

	/** called when projectile hits something */
	UFUNCTION()
	void OnHit(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
	
};
