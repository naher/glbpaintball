

#pragma once

#include "GameFramework/Character.h"
#include "PBCharacter.generated.h"

/**
 * 
 */
UCLASS()
class GLBPAINTBALL_API APBCharacter : public ACharacter
{

	GENERATED_UCLASS_BODY()
		
	virtual void Tick(float DeltaSeconds) override;

	virtual void BeginPlay() override;

	float TakeDamage(float DamageAmount,
					 struct FDamageEvent const& DamageEvent,
					 class AController* EventInstigator,
					 class AActor* DamageCauser) override;

	UFUNCTION(BlueprintCallable, Category = Energy)
	float GetEnergyLevel() const;

	UFUNCTION(BlueprintCallable, Category = Energy)
	void SetEnergyLevel(float NewEnergyLevel);

	UFUNCTION(BlueprintCallable, Category = Energy)
	float GetMaxEnergyLevel() const;

	UFUNCTION(BlueprintCallable, Category = Energy)
	void SetMaxEnergyLevel(float NewMaxEnergyLevel);

	UFUNCTION(BlueprintCallable, Category = Energy)
	float GetMinEnergyLevel() const;

	UFUNCTION(BlueprintCallable, Category = Energy)
	void SetMinEnergyLevel(float NewMinEnergyLevel);

	//sets jump flag when key is pressed
	UFUNCTION()
	void OnStartJump();

	//clears jump flag when key is released
	UFUNCTION()
	void OnStopJump();

	UFUNCTION()
	void OnFireStart();

	UFUNCTION()
	void OnFireEnd();

	//handles first<->third person camera
	void OnCameraToggle();

	/** Get weapon attach point from the first person mesh */
	FName GetWeaponAttachPoint() const;

	/*
	* Get either first or third person mesh.
	*
	* @param	WantFirstPerson		If true returns the first peron mesh, else returns the third
	*/
	USkeletalMeshComponent* GetSpecificPawnMesh(bool WantFirstPerson) const;

	UFUNCTION(BlueprintCallable, Category = Weapon)
	void EquipWeapon(class APBWeapon * Weapon);

	UFUNCTION(BlueprintCallable, Category = Weapon)
	void UnEquipWeapon();

	/** True if the player is moving */
	UFUNCTION()
    bool IsInMovement();

	/** Adds Weapon to inventory. Returns true if weapon added correctly, false otherwise. */
	UFUNCTION(BlueprintCallable, Category = Weapon)
	bool AddWeaponToInventory(class APBWeapon * Weapon);

	UFUNCTION(BlueprintCallable, Category = Weapon)
	APBWeapon * GetWeapon(UClass * WeaponClass) const;

	/** Add Energy to the character */
	UFUNCTION(BlueprintCallable, Category = Energy)
	void RechargeEnergy(float Energy);

	//ApplyDamage
	UFUNCTION(BlueprintCallable, Category = Energy)
	void ApplyDamage(float damage);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Audio Component")
	TSubobjectPtr <UAudioComponent> AudioCompDamageAction;

protected:

	bool bIsFirstPersonCamera;

	/** Energy level */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Energy)
	float EnergyLevel;

	/** Max Energy level */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Energy)
	float MaxEnergyLevel;

	/** Min Energy level */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Energy)
	float MinEnergyLevel;

	/** The factor of the Speed */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Energy)
	float SpeedFactor;

	/** The base Speed */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Energy)
	float BaseSpeed;

	/** The base health */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Health)
	float Health;

	/** Energy decay rate */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Energy)
	float EnergyDecayRate;

	/** socket or bone name for attaching weapon mesh */
	UPROPERTY(EditDefaultsOnly, Category = Weapon)
	FName WeaponAttachPoint;
	
	/** First person camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	TSubobjectPtr<UCameraComponent> FirstPersonCameraComponent;

	/** Pawn mesh: 1st person view (arms; seen only by self) */
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	TSubobjectPtr<USkeletalMeshComponent> FirstPersonMesh;

	/** default inventory list */
	UPROPERTY(EditDefaultsOnly, Category = Inventory)
	TArray<TSubclassOf<class APBWeapon> > DefaultInventoryClasses;

	/** weapons in inventory */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Transient, Category = Inventory)
	TArray<class APBWeapon*> Inventory;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Inventory)
	int32 InventorySize;

	/** Weapon held by the character */
	UPROPERTY(VisibleAnywhere, Category = Inventory)
	class APBWeapon * ActiveWeapon;

	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;

	//handles moving forward/backward
	UFUNCTION()
	void MoveForward(float Val);

	//handles strafing
	UFUNCTION()
	void MoveRight(float Val);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Audio Component")
	TSubobjectPtr <UAudioComponent> DamageAudioComp;

private:
	void SetScreenToDefaultScale();
};