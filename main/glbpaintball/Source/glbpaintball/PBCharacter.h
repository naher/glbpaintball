

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
	
	/** Energy level */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Energy)
	float EnergyLevel;

	/** The factor of the Speed */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Energy)
	float SpeedFactor;

	/** The base Speed */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Energy)
	float BaseSpeed;

	/** The base health */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Health)
	float Health;
	

	virtual void Tick(float DeltaSeconds) override;

	virtual void BeginPlay() override;

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

	//The player is in movement
	UFUNCTION()
    bool IsInMovement();

	/** Adds Weapon to inventory. Returns true if weapon added correctly, false otherwise. */
	UFUNCTION(BlueprintCallable, Category = Weapon)
	bool AddWeaponToInventory(class APBWeapon * Weapon);

	UFUNCTION(BlueprintCallable, Category = Weapon)
	APBWeapon * GetWeapon(UClass * WeaponClass) const;

protected:

	//Collect the energy
	UFUNCTION(BlueprintCallable, Category = Energy)
	void CollectEnergy();

	//This Function will called from CollectEnergy
	UFUNCTION(BlueprintImplementableEvent, Category = Energy)
	void RechargeEnergy(float Energy);

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

	bool bIsFirstPersonCamera;

	/** socket or bone name for attaching weapon mesh */
	UPROPERTY(EditDefaultsOnly, Category = Weapon)
	FName WeaponAttachPoint;

};