

#pragma once

#include "GameFramework/Character.h"
#include "Runtime/AIModule/Classes/AIController.h"
#include "PBEnemy.generated.h"

/**
 * 
 */
UCLASS()
class GLBPAINTBALL_API APBEnemy : public ACharacter
{
	GENERATED_UCLASS_BODY()

	void BeginPlay() override;

	void Tick(float DeltaSeconds) override;

private:

	virtual void SetNextTarget(); // refactor with movable objective?

	AAIController * Controller;

	FVector PointToChase;
	
};
