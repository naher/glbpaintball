

#include "glbpaintball.h"
#include "PBHUD.h"
#include "PBGameMode.h"
#include "PBCharacter.h"
#include "PBOnHitEffectsManager.h"
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
	//HUDClass = APBHUD::StaticClass();
}

void APBGameMode::BeginPlay()
{
	// Get Main Character.
	myCharacter = Cast<APBCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));

	GetWorld()->SpawnActor<APBOnHitEffectsManager>(APBOnHitEffectsManager::StaticClass());

	// Create HUDView in BP.
	OnCreateHUDView();

	// Register the PBEventController into Character.
	myCharacter->registerEventController(HUDView);
}
	
void APBGameMode::SetEnemyStatus(EnemyStatus NewStatus)
{
	GEnemyStatus = NewStatus;
}

EnemyStatus APBGameMode::GetEnemyStatus() const
{
	return GEnemyStatus;
}