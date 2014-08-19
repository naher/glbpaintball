

#pragma once

#include "FPSMovableObjective.h"
#include "FPSMovableInVolumeObjective.generated.h"

/**
 * 
 */
UCLASS()
class FPSPROJECT_API AFPSMovableInVolumeObjective : public AFPSMovableObjective
{
	GENERATED_UCLASS_BODY()

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Movement)
	UBoxComponent * MovementVolume;

private:

	FVector GetNextPointLocation() override;
	
};
