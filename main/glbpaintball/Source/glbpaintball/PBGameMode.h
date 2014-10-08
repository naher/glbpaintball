

#pragma once
#include "GameFramework/GameMode.h"
#include "PBHUDView.h"
#include "PBCharacter.h"
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

	bool _settedHUD;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = UI)
	UPBHUDView * HUDView;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = UI)
	APBCharacter * myCharacter;

	UFUNCTION(BlueprintImplementableEvent, Category = Energy)
	void OnCreateHUDView();

	virtual void BeginPlay() override;
};
