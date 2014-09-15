

#pragma once

#include "GameFramework/Actor.h"
#include "PBCharacter.h"
#include "PBPainPlataform.generated.h"

/**
 * 
 */
UCLASS()
class GLBPAINTBALL_API APBPainPlataform : public AActor
{
	GENERATED_UCLASS_BODY()

protected:

	// Static mesh of the pickup
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = PickUp)
	TSubobjectPtr<UStaticMeshComponent> PainMesh;

	/** The factor of the Speed */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Damage)
	float DamageSeverity;

	/** Character hit the painPlataform*/
	UPROPERTY(VisibleAnywhere, Category = Damage)
    bool IsCausingDamage;

	/** Character hit the painPlataform*/
	UPROPERTY(VisibleAnywhere, Category = Damage)
	class APBCharacter * ActiveCharacter;

	/** called upon the plataform generate damage */
	UFUNCTION()
	void InflictDamage();

	/** called upon the plataform generate damage */
	UFUNCTION()
	void StopInflictDamage(AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	/** called upon collision */
	UFUNCTION()
		void OnOverlap(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);
};
