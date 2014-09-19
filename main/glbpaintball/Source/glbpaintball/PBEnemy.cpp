

#include "glbpaintball.h"
#include "Runtime/AIModule/Classes/Navigation/NavigationComponent.h"
#include "PBEnemy.h"

#include <sstream>

APBEnemy::APBEnemy(const class FPostConstructInitializeProperties& PCIP)
	: Super(PCIP)
{
	// Default health value
	Health = 1.0f;
}

void APBEnemy::BeginPlay()
{
	Controller = Cast<AAIController>(GetController());

	SetNextTarget();
}

void APBEnemy::Tick(float DeltaSeconds)
{
	if (EPathFollowingRequestResult::Type::AlreadyAtGoal == 
			Controller->MoveToLocation(PointToChase, 0.2f, true, true, false))
	{
		SetNextTarget();
	}
}

float APBEnemy::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent,
							class AController* EventInstigator, class AActor* DamageCauser)
{
	if (IsPendingKill())
	{
		return 0;
	}

	Health -= DamageAmount;

	if (Health < 0.0f)
	{
		Destroy();
	}

	return DamageAmount;
}

void APBEnemy::SetNextTarget()
{
	PointToChase = Controller->NavComponent.Get()->GetRandomPointOnNavMesh().Location;
}