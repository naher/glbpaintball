

#include "glbpaintball.h"
#include "PBHUD.h"
#include "PBGameMode.h"
#include "PBCharacter.h"
#include "Kismet/GameplayStatics.h"


APBGameMode::APBGameMode(const class FPostConstructInitializeProperties& PCIP)
	: Super(PCIP)
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FObjectFinder<UBlueprint> PlayerPawnObject(TEXT("Blueprint'/Game/Blueprints/BP_Character.BP_Character'"));
	if (PlayerPawnObject.Object != NULL)
	{
		DefaultPawnClass = (UClass*)PlayerPawnObject.Object->GeneratedClass;
	}

	// use our HUD
	HUDClass = APBHUD::StaticClass();
}