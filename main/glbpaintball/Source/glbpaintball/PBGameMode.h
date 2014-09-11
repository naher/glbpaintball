

#pragma once
#include "GameFramework/GameMode.h"
#include "PBGameMode.generated.h"

/**
 * 
 */
UCLASS()
class GLBPAINTBALL_API APBGameMode : public AGameMode
{
	GENERATED_UCLASS_BODY()

	virtual void Tick(float DeltaSeconds) override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Energy)
	float DecayRate;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Energy)
    float MinimumEnergy;
		
};
