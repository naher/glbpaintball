

#pragma once
#include "GameFramework/GameMode.h"
#include "PBGameMode.generated.h"

UENUM(BlueprintType)
enum EnemyStatus { 
	PATROLLING UMETA(DisplayName = "Patrolling"),
	ATTACKING UMETA(DisplayName = "Attacking")
};

/**
 * 
 */
UCLASS()
class GLBPAINTBALL_API APBGameMode : public AGameMode
{
	GENERATED_UCLASS_BODY()

	void BeginPlay() override;

	UFUNCTION(BlueprintCallable, Category = Enemies)
	EnemyStatus GetEnemyStatus() const;

	UFUNCTION(BlueprintCallable, Category = Enemies)
	void SetEnemyStatus(EnemyStatus NewStatus);

protected:

	EnemyStatus GEnemyStatus;

};
