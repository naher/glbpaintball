

#include "glbpaintball.h"
#include "Runtime/AIModule/Classes/Navigation/NavigationComponent.h"
#include "PBEnemy.h"
#include "PBWeapon.h"
#include "PBCharacter.h"

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

	PlayerCharacter = Cast<APBCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));

	// Create new weapon and equip it
	FActorSpawnParameters SpawnInfo;
	SpawnInfo.bNoCollisionFail = true;
	Weapon = GetWorld()->SpawnActor<APBWeapon>(WeaponClass, SpawnInfo);
	if (Weapon)
	{
		Weapon->SetWeaponHolder(this);
		Weapon->SetAmmo(-1);
		Weapon->SetFiringSpeed(2);
		Weapon->SetTimeOnCooldown(1);
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

float APBEnemy::GetPatrolRadius() const
{
	return PatrolRadius;
}

float APBEnemy::GetAttackRange() const
{
	return AttackRange;
}

const FVector & APBEnemy::GetInitialLocation() const
{
	return InitialLocation;
}

EnemyStatus APBEnemy::GetStatus() const
{
	return ((APBGameMode*)GetWorld()->GetAuthGameMode())->GetEnemyStatus();
}

void APBEnemy::Attack()
{
	// Aim
	if (PlayerCharacter)
	{
		FaceAndRotateToPoint(PlayerCharacter->GetActorLocation(), 0.2f /*DeltaSeconds*/, ErrorMarginOnAim);
	}

	// Shoot
	if (Weapon)
	{
		Weapon->OnTriggerPress();
	}
}

void APBEnemy::ApplyWeaponRecoil()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Enemy Recoil"));
}

void APBEnemy::FaceAndRotateToPoint(const FVector & point, float deltaSeconds, float error)
{
	FVector ErrorVector(error, error, error);
	FBox AimBox(point - ErrorVector, point + ErrorVector);

	FRotator playerRot = FRotationMatrix::MakeFromX(FMath::RandPointInBox(AimBox) - GetActorLocation()).Rotator();
	playerRot.Pitch = GetActorRotation().Pitch;
	playerRot.Roll = GetActorRotation().Roll;
	FRotator newRot = FMath::RInterpTo(GetActorRotation(), playerRot, deltaSeconds, 9);

	FaceRotation(newRot);
	if (Controller)
	{
		Controller->SetControlRotation(newRot);
	}
}