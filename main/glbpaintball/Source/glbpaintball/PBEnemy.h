

#pragma once

#include "GameFramework/Character.h"
#include "Runtime/AIModule/Classes/AIController.h"
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

	void Tick(float DeltaSeconds) override;

	float TakeDamage(float DamageAmount, 
					 struct FDamageEvent const& DamageEvent, 
					 class AController* EventInstigator, 
					 class AActor* DamageCauser) override;

private:

	virtual void SetNextTarget(); // refactor with movable objective?

	AAIController * Controller;

	FVector PointToChase;
	
};
