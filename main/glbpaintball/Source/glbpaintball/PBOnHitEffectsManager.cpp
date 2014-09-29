

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
	}
}

void APBOnHitEffectsManager::NotifyHit()
{
	PlayerCameraManager->SetDesiredColorScale(OnHitScale, 0.1f);

	GetWorldTimerManager().SetTimer(this, &APBOnHitEffectsManager::SetScreenToDefaultScale, 0.1f, false);
}

void APBOnHitEffectsManager::SetScreenToDefaultScale()
{
	PlayerCameraManager->SetDesiredColorScale(DefaultScale, 0.5f);
}