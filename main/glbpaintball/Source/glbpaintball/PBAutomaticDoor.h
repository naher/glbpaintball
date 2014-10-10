

#pragma once

#include "PBInteractuable.h"
#include "GameFramework/Actor.h"
#include "PBAutomaticDoor.generated.h"

/**
 * 
 */
UCLASS()
class GLBPAINTBALL_API APBAutomaticDoor : public APBInteractuable
{
	GENERATED_UCLASS_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AutomaticDoor)
	float OpenDistance;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AutomaticDoor)
	FVector OriginalLocation;

	UFUNCTION(BlueprintCallable, Category = Interactuable)
	virtual void SetEnabled(bool enable) override;

	UFUNCTION(BlueprintCallable, Category = Interactuable)
	bool IsEnabled();

	UFUNCTION(BlueprintImplementableEvent, Category = AutomaticDoor)
	void OpenDoor();

	UFUNCTION(BlueprintImplementableEvent, Category = AutomaticDoor)
	void CloseDoor();

	virtual void BeginPlay() override;

protected:
	
	bool Enabled;

	// Static mesh of the door
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = AutomaticDoor)
	TSubobjectPtr<UStaticMeshComponent> DoorMesh;

	// Collision component to be used as root component
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Objective)
	TSubobjectPtr<UBoxComponent> BaseCollisionComponent;

	/** called upon the plataform generate damage */
	UFUNCTION()
	void OnEndOverlap(AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	/** called upon collision */
	UFUNCTION()
	void OnOverlap(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);


	


	
};
