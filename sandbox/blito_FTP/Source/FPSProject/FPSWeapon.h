

#pragma once

#include "GameFramework/Actor.h"
#include "FPSProjectile.h"
#include "FPSWeapon.generated.h"

/**
 * 
 */
UCLASS()
class FPSPROJECT_API AFPSWeapon : public AActor
{
	GENERATED_UCLASS_BODY()

	//** Current state of our weapon */
	enum EWeaponState { Idle, Firing };

	/** Pawn mesh: 1st person view (arms; seen only by self) */
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	TSubobjectPtr<USkeletalMeshComponent> WeaponMesh;

	/** Projectile class to spawn */
	UPROPERTY(EditDefaultsOnly, Category = Weapon)
	TSubclassOf<class AFPSProjectile> ProjectileClass;

	/** Gun muzzle's offset from the camera location */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Weapon)
	FVector MuzzleOffset;

	/** Bullets per second while holding the trigger */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Weapon)
	float FiringSpeed;

	/** Left ammunition */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Weapon)
	float Ammo;

	UFUNCTION()
	virtual void OnTriggerPress();

	UFUNCTION()
	virtual void OnTriggerRelease();

protected:
	virtual void Fire();

	
private:

	EWeaponState CurrentState;

};
