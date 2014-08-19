

#pragma once

#include "GameFramework/Character.h"
#include "FPSWeapon.h"
#include "FPSCharacter.generated.h"

/**
 * 
 */
UCLASS()
class FPSPROJECT_API AFPSCharacter : public ACharacter
{
	GENERATED_UCLASS_BODY()

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
	void EquipWeapon(AFPSWeapon * Weapon);

	UFUNCTION(BlueprintCallable, Category = Weapon)
	void UnEquipWeapon();

protected:
	/** First person camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	TSubobjectPtr<UCameraComponent> FirstPersonCameraComponent;

	/** Pawn mesh: 1st person view (arms; seen only by self) */
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	TSubobjectPtr<USkeletalMeshComponent> FirstPersonMesh;
	
	/** default inventory list */
	UPROPERTY(EditDefaultsOnly, Category = Inventory)
	TArray<TSubclassOf<class AFPSWeapon> > DefaultInventoryClasses;

	/** weapons in inventory */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Transient, Category = Inventory)
	TArray<class AFPSWeapon*> Inventory;

	/** Weapon held by the character */
	UPROPERTY(VisibleAnywhere, Category = Inventory)
	AFPSWeapon * ActiveWeapon;

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
