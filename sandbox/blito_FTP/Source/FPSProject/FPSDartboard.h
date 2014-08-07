

#pragma once

#include "FPSObjective.h"
#include "FPSDartboard.generated.h"

/**
 * 
 */
UCLASS()
class FPSPROJECT_API AFPSDartboard : public AFPSObjective
{
	GENERATED_UCLASS_BODY()

protected:
	void OnHit(AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit) override;
	
};
