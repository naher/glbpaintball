

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

	/** inits velocity of the projectile in the shoot direction */
	void InitVelocity(const FVector& ShootDirection);
	
protected:

	/** called when projectile hits something */
	UFUNCTION()
	void OnHit(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	/** Sphere collision component */
	UPROPERTY(VisibleDefaultsOnly, Category = Projectile)
	TSubobjectPtr<USphereComponent> CollisionComp;

	/** Projectile movement component */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Movement)
	TSubobjectPtr<class UProjectileMovementComponent> ProjectileMovement;

	/** Damage caused by the projectile (i.e. before mitigations) */
	UPROPERTY(EditAnywhere, Category = Projectile)
	float Damage;
	
};
