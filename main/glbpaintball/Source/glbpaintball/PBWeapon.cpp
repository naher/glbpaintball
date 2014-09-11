

#include "glbpaintball.h"
#include "PBCharacter.h"
#include "PBProjectile.h"
#include "PBWeapon.h"


APBWeapon::APBWeapon(const class FPostConstructInitializeProperties& PCIP)
	: Super(PCIP)
{
	Ammo = 10;
	CurrentState = EWeaponState::Idle;
	WeaponMesh = PCIP.CreateDefaultSubobject<USkeletalMeshComponent>(this, TEXT("FirstPersonMesh"));
	WeaponMesh->SetHiddenInGame(true);
}

void APBWeapon::OnTriggerPress()
{
	if (CurrentState != EWeaponState::OnCooldown)
	{
		Fire();
	}
}

void APBWeapon::OnTriggerRelease()
{
	if (isAutomatic) // if weapon is automatic, stop firing when we release the trigger
	{
		// delete existing timers
		GetWorldTimerManager().SetTimer(this, &APBWeapon::Fire, -1, false);
	}
}

void APBWeapon::OnEquip(APBCharacter * WeaponOwner)
{
	FName AttachPoint = WeaponOwner->GetWeaponAttachPoint();
	USkeletalMeshComponent * FirstPersonMesh = WeaponOwner->GetSpecificPawnMesh(true);

	WeaponMesh->AttachTo(FirstPersonMesh, AttachPoint, EAttachLocation::SnapToTarget);
	WeaponMesh->SetHiddenInGame(false);
	Instigator = WeaponOwner;
	WeaponHolder = WeaponOwner;
}

void APBWeapon::OnUnEquip()
{
	WeaponMesh->DetachFromParent();
	WeaponMesh->SetHiddenInGame(true);
}

int32 APBWeapon::GetSlotNumber() const
{
	return SlotNumber;
}

void APBWeapon::AddAmmo(int32 AmmoInc)
{
	Ammo += AmmoInc;
}

void APBWeapon::Fire()
{
	if (Ammo > 0)
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
				APBProjectile* const Projectile = World->SpawnActor<APBProjectile>(ProjectileClass, MuzzleLocation, MuzzleRotation, SpawnParams);
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

		// if we have to keep shooting, call Fire() again in a while
		if (CurrentState == EWeaponState::Firing && isAutomatic && FiringSpeed > 0)
		{
			GetWorldTimerManager().SetTimer(this, &APBWeapon::Fire, 1 / FiringSpeed, true);
		}
		
		//set it on cooldown if needed
		if (TimeOnCooldown > 0)
		{
			CurrentState = EWeaponState::OnCooldown;
			GetWorldTimerManager().SetTimer(this, &APBWeapon::SetOffCooldown, TimeOnCooldown, false);
		}
		else
		{
			CurrentState = EWeaponState::Idle;
		}

	}
}