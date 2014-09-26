

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

	void BeginPlay() override;
};
