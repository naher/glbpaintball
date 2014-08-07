

#pragma once

#include "GameFramework/GameMode.h"
#include "FPSGameMode.generated.h"

/**
 * 
 */
UCLASS()
class FPSPROJECT_API AFPSGameMode : public AGameMode
{
	GENERATED_UCLASS_BODY()

	virtual void BeginPlay() override;
	
};
