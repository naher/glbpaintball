
#include "FPSProject.h"
#include "FPSGameMode.h"
#include "FPSHUD.h"


AFPSGameMode::AFPSGameMode(const class FPostConstructInitializeProperties& PCIP)
	: Super(PCIP)
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FObjectFinder<UBlueprint> PlayerPawnObject(TEXT("Blueprint'/Game/Blueprints/BP_FPSCharacter.BP_FPSCharacter'"));
	if (PlayerPawnObject.Object != NULL)
	{
		DefaultPawnClass = (UClass*)PlayerPawnObject.Object->GeneratedClass;
	}

	// use our HUD
	HUDClass = AFPSHUD::StaticClass();
}

void AFPSGameMode::BeginPlay()
{
	Super::BeginPlay();

	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, TEXT("HELLO WORLD"));
	}
}
