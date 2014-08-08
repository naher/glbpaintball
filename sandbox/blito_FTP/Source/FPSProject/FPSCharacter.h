

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
	
	//handles first<->third person camera
	void OnCameraToggle();

	/** First person camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	TSubobjectPtr<UCameraComponent> FirstPersonCameraComponent;

	/** Pawn mesh: 1st person view (arms; seen only by self) */
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	TSubobjectPtr<USkeletalMeshComponent> FirstPersonMesh;
	
	/** Projectile class to spawn */
	UPROPERTY(EditDefaultsOnly, Category = Weapon)
	TSubclassOf<class AFPSProjectile> ProjectileClass;

	/** Weapon held by the character */
	UPROPERTY(VisibleAnywhere, Category = Weapon)
	AFPSWeapon * Weapon;

protected:
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;
	
	//handles moving forward/backward
	UFUNCTION()
	void MoveForward(float Val);

	//handles strafing
	UFUNCTION()
	void MoveRight(float Val);

	bool bIsFirstPersonCamera;

};
