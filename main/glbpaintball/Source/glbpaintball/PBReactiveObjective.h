

#pragma once

#include "PBObjective.h"
#include "PBReactiveObjective.generated.h"

/**
 * 
 */
UCLASS()
class GLBPAINTBALL_API APBReactiveObjective : public APBObjective
{
	GENERATED_UCLASS_BODY()

	UFUNCTION()
	virtual void Tick(float DeltaSeconds) override;

	virtual void BeginPlay() override;

protected:
	/** Initial position of the objective's movement */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Movement)
	ATargetPoint* FromPoint;

	/** Final position of the objective's movement */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Movement)
	ATargetPoint* ToPoint;

	/** Point used as a reference to calculate distance */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Movement)
	ATargetPoint* MonitorPoint;

	/** Minimum distance from the monitor for the objective to react */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Movement)
	float MinDist;

	/** Maximum distance from the monitor for the objective to react */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Movement)
	float MaxDist;

private:
	AActor * PlayerCharacter;
	
};
