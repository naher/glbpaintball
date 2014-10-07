

#pragma once

#include "GameFramework/Character.h"
#include "Runtime/AIModule/Classes/AIController.h"
#include "PBGameMode.h"
#include "PBEnemy.generated.h"

/**
 * 
 */
UCLASS()
class GLBPAINTBALL_API APBEnemy : public ACharacter
{
	GENERATED_UCLASS_BODY()
	
	void BeginPlay() override;

	float TakeDamage(float DamageAmount, 
					 struct FDamageEvent const& DamageEvent, 
					 class AController* EventInstigator, 
					 class AActor* DamageCauser) override;

	float GetPatrolRadius() const;

	const FVector & GetInitialLocation() const;

	EnemyStatus GetStatus() const;

	void Attack();

protected:

	/** Radius used when patrolling. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AI)
	float PatrolRadius;

	/** Weapon held by this objetive */
	UPROPERTY(EditAnywhere, Category = Weapon)
	TSubclassOf<class APBWeapon> WeaponClass;

	/** Health, reduced linearly with damage. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Health)
	float Health;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Difficulty)
	float ErrorMarginOnAim;

	/** Set the view to the character face **/
	UFUNCTION()
	void FaceAndRotateToPoint(const FVector & point, float deltaSeconds, float error);

private:

	AAIController * Controller;

	FVector InitialLocation;

	class APBWeapon * Weapon;

	class APBCharacter * PlayerCharacter;
	
};
