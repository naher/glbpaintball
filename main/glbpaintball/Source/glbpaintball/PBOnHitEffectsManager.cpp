

#include "glbpaintball.h"
#include "PBCharacter.h"
#include "PBOnHitEffectsManager.h"


APBOnHitEffectsManager::APBOnHitEffectsManager(const class FPostConstructInitializeProperties& PCIP)
	: Super(PCIP)
{
	DefaultScale = FVector(1.0f, 1.0f, 1.0f);
	OnHitScale = FVector(0.5f, 0.0f, 0.0f);
}

void APBOnHitEffectsManager::BeginPlay()
{
	PlayerCameraManager = UGameplayStatics::GetPlayerCameraManager(this, 0);

	// Set ourselves as observers
	Character = Cast<APBCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	if (Character)
	{
		Character->SetOnHitEffectsManager(this);
		PlayerCamera = Character->GetCamera();
		if (PlayerCamera) {
			PlayerCamera->PostProcessSettings.bOverride_VignetteColor = true;
			PlayerCamera->PostProcessSettings.bOverride_VignetteIntensity = true;
			PlayerCamera->PostProcessSettings.VignetteColor = FLinearColor(0.2f, 0.0f, 0.0f);
			PlayerCamera->PostProcessSettings.VignetteIntensity = 0.0f;
		}
	}
}

void APBOnHitEffectsManager::NotifyHit()
{
	PlayerCameraManager->SetDesiredColorScale(OnHitScale, 0.1f);

	GetWorldTimerManager().SetTimer(this, &APBOnHitEffectsManager::SetScreenToDefaultScale, 0.1f, false);

	// Change the scale color if low health
	if (!Character || !PlayerCamera)
		return;

	float EnergyPercentage = (Character->GetEnergyLevel() - Character->GetMinEnergyLevel())
							/ (Character->GetMaxEnergyLevel() - Character->GetMinEnergyLevel());

	PlayerCamera->PostProcessSettings.VignetteIntensity = EnergyPercentage < 0.2f ? 1.0f : 0.0f;
}

void APBOnHitEffectsManager::SetScreenToDefaultScale()
{
	PlayerCameraManager->SetDesiredColorScale(DefaultScale, 0.5f);
}