

#include "glbpaintball.h"
#include "PBReactiveObjective.h"


APBReactiveObjective::APBReactiveObjective(const class FPostConstructInitializeProperties& PCIP)
	: Super(PCIP)
{
	PrimaryActorTick.bCanEverTick = true;
}

void APBReactiveObjective::BeginPlay()
{
	PlayerCharacter = (*(GetWorld()->GetPlayerControllerIterator()))->GetPawn();
}

void APBReactiveObjective::Tick(float DeltaSeconds)
{
  if (PlayerCharacter != NULL && MonitorPoint != NULL)
  {
	FVector PlayerToMonitor = MonitorPoint->GetActorLocation() - PlayerCharacter->GetActorLocation();

	// f(MaxDist)=0 = FromPoint.Location
	float MovementRatio = 1 - FMath::Clamp<float>(PlayerToMonitor.Size(), MinDist, MaxDist) / MaxDist;
	
	FVector NewLocation = FMath::Lerp<FVector, float>(FromPoint->GetActorLocation(), ToPoint->GetActorLocation(), MovementRatio);

	SetActorLocation(NewLocation);
  }
}
