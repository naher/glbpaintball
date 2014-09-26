

#include "glbpaintball.h"
#include "PBCharacter.h"
#include "PBOnHitEffectsManager.h"


APBOnHitEffectsManager::APBOnHitEffectsManager(const class FPostConstructInitializeProperties& PCIP)
	: Super(PCIP)
{

}

void APBOnHitEffectsManager::BeginPlay()
{
	PlayerCameraManager = UGameplayStatics::GetPlayerCameraManager(this, 0);

	// Set ourselves as observers
	APBCharacter * Character = Cast<APBCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	if (Character)
	{
		Character->SetOnHitEffectsManager(this);
	}
}

void APBOnHitEffectsManager::NotifyHit()
{
	PlayerCameraManager->SetDesiredColorScale(FVector(1.0f, 0.0f, 0.0f), 0.1f);

	GetWorldTimerManager().SetTimer(this, &APBOnHitEffectsManager::SetScreenToDefaultScale, 0.1f, false);
}

void APBOnHitEffectsManager::SetScreenToDefaultScale()
{
	PlayerCameraManager->SetDesiredColorScale(FVector(1.0f, 1.0f, 1.0f), 0.5f);
}