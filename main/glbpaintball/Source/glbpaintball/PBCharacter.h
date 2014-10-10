

#pragma once

#include "PBEventController.h"
#include "PBWeaponHolder.h"
#include "GameFramework/Character.h"
#include "PBCharacter.generated.h"

/**
 * 
 */

UENUM(BlueprintType)
enum EnumCharacterMovementStatus
{
	ESM_Walking UMETA(DisplayName = "Walk"),
	ESM_Running UMETA(DisplayName = "Run"),
	ESM_Jumping UMETA(DisplayName = "Jump"),
};

UCLASS()
class GLBPAINTBALL_API APBCharacter : public ACharacter, public IPBWeaponHolder
{

	GENERATED_UCLASS_BODY()

	/** AnimMontage to play each time we fire */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animations)
	class UAnimMontage* FireAnimation;
		
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

	UFUNCTION(BlueprintCallable, Category = Camera)
	UCameraComponent * GetCamera() const;

	//sets jump flag when key is pressed
	UFUNCTION()
	void OnStartJump();

	//clears jump flag when key is released
	UFUNCTION()
	void OnStopJump();

	UFUNCTION()
	void OnFireStart();

	//clears jump flag when key is released
	UFUNCTION()
	void OnRunStart();

	UFUNCTION()
	void OnRunEnd();

	UFUNCTION()
	void OnFireEnd();

	UFUNCTION()
	void SetMovementStatus(int32 status);

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

	/** True if the player is moving */
	UFUNCTION()
	bool IsRunning();

	/** Adds Weapon to inventory. Returns true if weapon added correctly, false otherwise. */
	UFUNCTION(BlueprintCallable, Category = Weapon)
	bool AddWeaponToInventory(class APBWeapon * Weapon);

	UFUNCTION(BlueprintCallable, Category = Weapon)
	APBWeapon * GetWeapon(UClass * WeaponClass) const;

	/** Add Energy to the character */
	UFUNCTION(BlueprintCallable, Category = Energy)
	void RechargeEnergy(float Energy);

	/** StartAttack Audio Component*/
	UPROPERTY(EditDefaultsOnly, Category = Audio)
	USoundCue * SoundDamage;

	UFUNCTION()
	void SetOnHitEffectsManager(class APBOnHitEffectsManager * Manager);
	
	UFUNCTION(BlueprintCallable, Category = Weapon)
	virtual void ApplyWeaponRecoil() override;

	void registerEventController(IPBEventController * controller);

protected:

	IPBEventController * EventController;

	bool bIsFirstPersonCamera;

	/** Energy level */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Energy)
	float EnergyLevel;

	/** Energy level */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Energy)
	float NormalSpeedEnergy;

	/** Max Energy level */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Energy)
	float MaxEnergyLevel;

	/** Min Energy level */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Energy)
	float MinEnergyLevel;

	/** The factor of the Speed */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Energy)
	float SpeedFactor;

	/** The factor of the Speed walking */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Energy)
	float SpeedFactorWalk;

	/** The factor of the Speed running*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Energy)
	float SpeedFactorRun;

	/** The base Speed */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Energy)
	float BaseSpeed;

	/**Movement Status of the Objective */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Movement)
	int32 MovementStatus;

	/**Movement Status of the Objective */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Movement)
	int32 PrevMovementStatus;

	/** The base health */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Health)
	float Health;

	/** Energy decay rate */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Energy)
	float EnergyDecayRate;

	/** Energy decay rate Walk */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Energy)
	float EnergyDecayRateWalk;

	/** Energy decay rate Run */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Energy)
	float EnergyDecayRateRun;

	/** Energy decay rate Jump */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Energy)
	float EnergyDecayRateJump;

	/** socket or bone name for attaching weapon mesh */
	UPROPERTY(EditDefaultsOnly, Category = Weapon)
	FName WeaponAttachPoint;
	
	/** First person camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	TSubobjectPtr<UCameraComponent> FirstPersonCameraComponent;

	/** Pawn mesh: 1st person view (arms; seen only by self) */
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	TSubobjectPtr<USkeletalMeshComponent> FirstPersonMesh;


	// Collision component to be used as root component
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Mesh)
	TSubobjectPtr<USphereComponent> BaseCollisionComponent;
	
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

	/** Object responsible for On Hit effects */
	class APBOnHitEffectsManager * OnHitEffectsManager;

	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;

	//handles moving forward/backward
	UFUNCTION()
	void MoveForward(float Val);

	//handles strafing
	UFUNCTION()
	void MoveRight(float Val);

	//Check Objects to interact
	UFUNCTION()
	void Interact();

	//Update the speed o the Movement Animation
	UFUNCTION()
	void UpdateAnimationMovementRate(float rate);


private:
	void SetScreenToDefaultScale();
};