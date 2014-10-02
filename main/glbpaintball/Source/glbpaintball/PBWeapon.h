

#pragma once

#include "PBWeaponHolder.h"
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

	UFUNCTION(BlueprintCallable, Category = Weapon)
	int32 GetAmmo() const;

	/** Overrides the current Ammo. Does not consider limits. */
	UFUNCTION(BlueprintCallable, Category = Weapon)
	void SetAmmo(int32 NewAmmo);

	UFUNCTION(BlueprintCallable, Category = Weapon)
	void SetMaxAmmo(int32 Max);

	UFUNCTION(BlueprintCallable, Category = Weapon)
	void SetFiringSpeed(float bulletsPerSecond);

	UFUNCTION(BlueprintCallable, Category = Weapon)
	void SetTimeOnCooldown(float time);

	UFUNCTION(BlueprintCallable, Category = Weapon)
	int32 GetMaxAmmo() const;

	UFUNCTION(BlueprintCallable, Category = Weapon)
	AActor * GetWeaponHolder() const;

	/** Sets the weapon holder. See OnEquip. */
	UFUNCTION(BlueprintCallable, Category = Weapon)
	void SetWeaponHolder(TScriptInterface<IPBWeaponHolder> * Holder);

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

	/** Left ammunition. (ammo < 0: unlimited ammo) */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Weapon)
	int32 Ammo;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Weapon)
	int32 MaxAmmo;

	/** true if this weapon can fire several bullets on a single click */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Weapon)
	bool isAutomatic;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Audio Component")
	TSubobjectPtr <UAudioComponent> AudioComp;

	TScriptInterface<IPBWeaponHolder> * WeaponHolder;


private:
	EWeaponState CurrentState;
	
};
