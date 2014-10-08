

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
	_settedHUD = false;

	DecayRate = 0.01f;
	MinimumEnergy = 2;
}

void APBGameMode::BeginPlay()
{
	// Get Main Character.
	myCharacter = Cast<APBCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));

	// Create HUDView in BP.
	OnCreateHUDView();

	// Register the PBEventController into Character.
	myCharacter->registerEventController(HUDView);
}

void APBGameMode::Tick(float DeltaSeconds)
{
	if (myCharacter != NULL)
	{
	if (myCharacter->IsInMovement() && myCharacter->GetEnergyLevel() > MinimumEnergy)
	 {
		myCharacter->SetEnergyLevel(FMath::FInterpTo(myCharacter->GetEnergyLevel(), 0.f, DeltaSeconds, DecayRate));
		//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, "Reduce Speed");
	 }
	}

	
}