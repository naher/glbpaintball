

#pragma once
#include "GameFramework/Actor.h"
#include "PBInteractuable.h"
#include "PBButton.generated.h"

/**
 * 
 */
UCLASS()
class GLBPAINTBALL_API APBButton : public AActor
{
   GENERATED_UCLASS_BODY()

   UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Button)
	APBInteractuable * Target;

   /** StartAttack Audio Component*/
   UPROPERTY(EditDefaultsOnly, Category = Audio)
   USoundCue * ActivateSound;
	
	UFUNCTION()
	void Push();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Button)
	bool Action;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Button)
	bool Recyclable;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Button)
	bool Active;

	// Static mesh of the Button
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Mesh)
	TSubobjectPtr<UStaticMeshComponent> ButtonMesh;

	// Collision component to be used as root component
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Objective)
	TSubobjectPtr<USphereComponent> BaseCollisionComponent;

	/** called up on collision */
	UFUNCTION()
	void OnOverlap(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);



};
