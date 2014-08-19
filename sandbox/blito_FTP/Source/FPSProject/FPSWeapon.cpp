

#include "FPSProject.h"
#include "FPSCharacter.h"
#include "FPSWeapon.h"


AFPSWeapon::AFPSWeapon(const class FPostConstructInitializeProperties& PCIP)
	: Super(PCIP)
{
	Ammo = 10;
	CurrentState = EWeaponState::Idle;
	WeaponMesh = PCIP.CreateDefaultSubobject<USkeletalMeshComponent>(this, TEXT("FirstPersonMesh"));
	WeaponMesh->SetHiddenInGame(true);
}

void AFPSWeapon::OnTriggerPress()
{
	if (Ammo > 0)
	{
		Fire();
		
		// if we have to keep shooting, call Fire() again in a while
		if (CurrentState == EWeaponState::Firing && FiringSpeed > 0)
		{
			GetWorldTimerManager().SetTimer(this, &AFPSWeapon::Fire, 1 / FiringSpeed, false);
		}
	}
}

void AFPSWeapon::OnTriggerRelease()
{
	// delete existing timers
	GetWorldTimerManager().SetTimer(this, &AFPSWeapon::Fire, -1, false);

	// set the new state of the weapon
	CurrentState = EWeaponState::Idle;
}

void AFPSWeapon::OnEquip(AFPSCharacter * WeaponOwner)
{
	FName AttachPoint = WeaponOwner->GetWeaponAttachPoint();
	USkeletalMeshComponent * FirstPersonMesh = WeaponOwner->GetSpecificPawnMesh(true);

	WeaponMesh->AttachTo(FirstPersonMesh, AttachPoint, EAttachLocation::SnapToTarget);
	WeaponMesh->SetHiddenInGame(false);
	Instigator = WeaponOwner;
	WeaponHolder = WeaponOwner;
}

void AFPSWeapon::OnUnEquip()
{
	WeaponMesh->DetachFromParent();
	WeaponMesh->SetHiddenInGame(true);
}

void AFPSWeapon::Fire()
{
	// try and fire a projectile
	if (ProjectileClass != NULL)
	{
		// Get the camera transform
		FVector CameraLoc;
		FRotator CameraRot;
		WeaponHolder->GetActorEyesViewPoint(CameraLoc, CameraRot);
		// MuzzleOffset is in camera space, so transform it to world space before offsetting from the camera to find the final muzzle position
		FVector const MuzzleLocation = CameraLoc + FTransform(CameraRot).TransformVector(MuzzleOffset);
		FRotator MuzzleRotation = CameraRot;
		MuzzleRotation.Pitch += 10.0f;          // skew the aim upwards a bit
		UWorld* const World = GetWorld();
		if (World)
		{
			FActorSpawnParameters SpawnParams;
			SpawnParams.Owner = this;
			SpawnParams.Instigator = Instigator;
			// spawn the projectile at the muzzle
			AFPSProjectile* const Projectile = World->SpawnActor<AFPSProjectile>(ProjectileClass, MuzzleLocation, MuzzleRotation, SpawnParams);
			if (Projectile)
			{
				// find launch direction
				FVector const LaunchDir = MuzzleRotation.Vector();
				Projectile->InitVelocity(LaunchDir);

				// set the new state of the weapon
				CurrentState = EWeaponState::Firing;

				// reduce the ammo left
				Ammo--;
			}
		}
	}
}