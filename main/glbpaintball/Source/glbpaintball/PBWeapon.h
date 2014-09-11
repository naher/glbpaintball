

#pragma once

#include "GameFramework/Actor.h"
#include "PBWeapon.generated.h"

/**
 * 
 */
UCLASS()
class GLBPAINTBALL_API APBWeapon : public AActor
{
	GENERATED_UCLASS_BODY()

	//** Current state of our weapon */
	enum EWeaponState { Idle, Firing, OnCooldown };

	UFUNCTION()
	virtual void OnTriggerPress();

	UFUNCTION()
	virtual void OnTriggerRelease();

	UFUNCTION()
	virtual void OnEquip(class APBCharacter * WeaponOwner);

	UFUNCTION()
	virtual void OnUnEquip();

	UFUNCTION(BlueprintCallable, Category = Weapon)
	int32 GetSlotNumber() const;

	UFUNCTION()
	void AddAmmo(int32 AmmoInc);

protected:
	virtual void Fire();

	inline void SetOffCooldown() { CurrentState = EWeaponState::Idle; }

	/** Pawn mesh: 1st person view (arms; seen only by self) */
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	TSubobjectPtr<USkeletalMeshComponent> WeaponMesh;

	/** Projectile class to spawn */
	UPROPERTY(EditDefaultsOnly, Category = Weapon)
	TSubclassOf<class APBProjectile> ProjectileClass;

	/** Key used to equip this weapon */
	UPROPERTY(EditDefaultsOnly, Category = Weapon)
	int32 SlotNumber;

	/** Gun muzzle's offset from the camera location */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Weapon)
	FVector MuzzleOffset;

	/** Bullets per second while holding the trigger */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Weapon)
	float FiringSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Weapon)
	float TimeOnCooldown;

	/** Left ammunition */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Weapon)
	float Ammo;

	/** true if this weapon can fire several bullets on a single click */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Weapon)
	bool isAutomatic;

	class APBCharacter * WeaponHolder;


private:
	EWeaponState CurrentState;
	
};
