

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

	/** Health, reduced linearly with damage. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Health)
	float Health;

	void BeginPlay() override;

	float TakeDamage(float DamageAmount, 
					 struct FDamageEvent const& DamageEvent, 
					 class AController* EventInstigator, 
					 class AActor* DamageCauser) override;

	float GetPatrolRadius() const;

	const FVector & GetInitialLocation() const;

	EnemyStatus GetStatus() const;

protected:

	/** Radius used when patrolling. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AI)
	float PatrolRadius;

private:

	AAIController * Controller;

	FVector InitialLocation;
	
};
