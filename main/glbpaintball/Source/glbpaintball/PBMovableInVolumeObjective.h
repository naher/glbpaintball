

#pragma once

#include "PBMovableObjective.h"
#include "PBMovableInVolumeObjective.generated.h"

/**
 * 
 */
UCLASS()
class GLBPAINTBALL_API APBMovableInVolumeObjective : public APBMovableObjective
{
	GENERATED_UCLASS_BODY()

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Objective)
	UBoxComponent * MovementVolume;

private:

	FVector GetNextPointLocation() override;
	
};
