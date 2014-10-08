

#pragma once

#include "GameFramework/Character.h"
#include "Runtime/AIModule/Classes/AIController.h"
#include "PBGameMode.h"
#include "PBWeaponHolder.h"
#include "PBEnemy.generated.h"

/**
 * 
 */
UCLASS()
class GLBPAINTBALL_API APBEnemy : public ACharacter, public IPBWeaponHolder
{
	GENERATED_UCLASS_BODY()
	
	void BeginPlay() override;

	float TakeDamage(float DamageAmount, 
					 struct FDamageEvent const& DamageEvent, 
					 class AController* EventInstigator, 
					 class AActor* DamageCauser) override;

	UFUNCTION(BlueprintCallable, Category = Weapon)
	float GetPatrolRadius() const;

	UFUNCTION(BlueprintCallable, Category = Weapon)
	float GetAttackRange() const;

	const FVector & GetInitialLocation() const;

	EnemyStatus GetStatus() const;

	void Attack();

	UFUNCTION(BlueprintCallable, Category = Weapon)
	virtual void ApplyWeaponRecoil() override;

protected:

	/** Radius used when patrolling. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AI)
	float PatrolRadius;

	/** Minimum distance between Enemy and Player to start attacking */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AI)
	float AttackRange;

	/** Aiming error */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AI)
	float ErrorMarginOnAim;

	/** Weapon held by this objetive */
	UPROPERTY(EditAnywhere, Category = Weapon)
	TSubclassOf<class APBWeapon> WeaponClass;

	/** Health, reduced linearly with damage. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Health)
	float Health;
	
	/** Set the view to the character face **/
	UFUNCTION()
	void FaceAndRotateToPoint(const FVector & point, float deltaSeconds, float error);

private:

	AAIController * Controller;

	FVector InitialLocation;

	class APBWeapon * Weapon;

	class APBCharacter * PlayerCharacter;
	
};
