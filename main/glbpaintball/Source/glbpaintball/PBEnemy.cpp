

#include "glbpaintball.h"
#include "Runtime/AIModule/Classes/Navigation/NavigationComponent.h"
#include "PBEnemy.h"

APBEnemy::APBEnemy(const class FPostConstructInitializeProperties& PCIP)
	: Super(PCIP)
{
	// Default health value
	Health = 1.0f;
}

void APBEnemy::BeginPlay()
{
	Controller = Cast<AAIController>(GetController());

	InitialLocation = GetActorLocation();
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

float APBEnemy::GetPatrolRadius() const
{
	return PatrolRadius;
}

const FVector & APBEnemy::GetInitialLocation() const
{
	return InitialLocation;
}

EnemyStatus APBEnemy::GetStatus() const
{
	return ((APBGameMode*)GetWorld()->GetAuthGameMode())->GetEnemyStatus();
}