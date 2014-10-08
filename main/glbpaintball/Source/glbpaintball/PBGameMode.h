

#pragma once
#include "GameFramework/GameMode.h"
#include "PBHUDView.h"
#include "PBCharacter.h"
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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = UI)
	UPBHUDView * HUDView;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = UI)
	APBCharacter * myCharacter;

	UFUNCTION(BlueprintImplementableEvent, Category = Energy)
	void OnCreateHUDView();
};
