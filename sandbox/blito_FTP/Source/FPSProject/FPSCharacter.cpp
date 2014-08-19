

#include "FPSProject.h"
#include "FPSProjectile.h"
#include "FPSWeapon.h"
#include "FPSCharacter.h"


AFPSCharacter::AFPSCharacter(const class FPostConstructInitializeProperties& PCIP)
	: Super(PCIP)
{
	// Start game in first person mode
	bIsFirstPersonCamera = true;

	// Create a CameraComponent 
	FirstPersonCameraComponent = PCIP.CreateDefaultSubobject<UCameraComponent>(this, TEXT("FirstPersonCamera"));
	FirstPersonCameraComponent->AttachParent = CapsuleComponent;

	// Position the camera a bit above the eyes
	FirstPersonCameraComponent->RelativeLocation = FVector(0, 0, 50.0f + BaseEyeHeight);

	// Create a mesh component that will be used when being viewed from a '1st person' view (when controlling this pawn)
	FirstPersonMesh = PCIP.CreateDefaultSubobject<USkeletalMeshComponent>(this, TEXT("FirstPersonMesh"));
	FirstPersonMesh->SetOnlyOwnerSee(true);         // only the owning player will see this mesh
	FirstPersonMesh->AttachParent = FirstPersonCameraComponent;
	FirstPersonMesh->bCastDynamicShadow = false;
	FirstPersonMesh->CastShadow = false;

	// everyone but the owner can see the regular body mesh
	Mesh->SetOwnerNoSee(true);

	ActiveWeapon = nullptr;
}

void AFPSCharacter::BeginPlay()
{
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, TEXT("Using FPSCharacter"));
	}

	for (auto WeaponClass : DefaultInventoryClasses)
	{
		// Create new weapon and equip it
		FActorSpawnParameters SpawnInfo;
		SpawnInfo.bNoCollisionFail = true;
		AFPSWeapon* NewWeapon = GetWorld()->SpawnActor<AFPSWeapon>(WeaponClass, SpawnInfo);
		Inventory.Add(NewWeapon);
	}
}

void AFPSCharacter::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	// set up gameplay key bindings
	InputComponent->BindAxis("MoveForward", this, &AFPSCharacter::MoveForward);
	InputComponent->BindAxis("MoveRight", this, &AFPSCharacter::MoveRight);
	InputComponent->BindAxis("Turn", this, &AFPSCharacter::AddControllerYawInput);
	InputComponent->BindAxis("LookUp", this, &AFPSCharacter::AddControllerPitchInput);
	InputComponent->BindAction("Jump", IE_Pressed, this, &AFPSCharacter::OnStartJump);
	InputComponent->BindAction("Jump", IE_Released, this, &AFPSCharacter::OnStopJump);
	InputComponent->BindAction("Change_Camera", IE_Pressed, this, &AFPSCharacter::OnCameraToggle);
	InputComponent->BindAction("Fire", IE_Pressed, this, &AFPSCharacter::OnFireStart);
	InputComponent->BindAction("Fire", IE_Released, this, &AFPSCharacter::OnFireEnd);
}

void AFPSCharacter::MoveForward(float Value)
{
	if ((Controller != NULL) && (Value != 0.0f))
	{
		// find out which way is forward
		FRotator Rotation = Controller->GetControlRotation();
		// Limit pitch when walking or falling
		if (CharacterMovement->IsMovingOnGround() || CharacterMovement->IsFalling())
		{
			Rotation.Pitch = 0.0f;
		}
		// add movement in that direction
		const FVector Direction = FRotationMatrix(Rotation).GetScaledAxis(EAxis::X);
		AddMovementInput(Direction, Value);
	}
}

void AFPSCharacter::MoveRight(float Value)
{
	if ((Controller != NULL) && (Value != 0.0f))
	{
		// find out which way is right
		const FRotator Rotation = Controller->GetControlRotation();
		const FVector Direction = FRotationMatrix(Rotation).GetScaledAxis(EAxis::Y);
		// add movement in that direction
		AddMovementInput(Direction, Value);
	}
}

void AFPSCharacter::OnStartJump()
{
	bPressedJump = true;
}

void AFPSCharacter::OnStopJump()
{
	bPressedJump = false;
}

void AFPSCharacter::OnFireStart()
{
	if (ActiveWeapon)
	{
		ActiveWeapon->OnTriggerPress();
	}
}

void AFPSCharacter::OnFireEnd()
{
	if (ActiveWeapon)
	{
		ActiveWeapon->OnTriggerRelease();
	}
}

void AFPSCharacter::OnCameraToggle()
{
	// Set the new position of the camera
	bIsFirstPersonCamera = !bIsFirstPersonCamera;

	// Switch to first person camera
	if (bIsFirstPersonCamera)
	{
		// Position the camera a bit above the eyes
		FirstPersonCameraComponent->SetRelativeLocation(FVector(0, 0, 50.0f + BaseEyeHeight));

		// everyone but the owner can see the regular body mesh
		FirstPersonMesh->SetOwnerNoSee(false);
		Mesh->SetOwnerNoSee(true);
	}
	// Switch to third person camera
	else
	{
		// Position the camera a bit above the eyes
		FirstPersonCameraComponent->SetRelativeLocation(FVector(-180, 0, 50.0f + BaseEyeHeight));

		// everyone can see the regular body mesh
		FirstPersonMesh->SetOwnerNoSee(true);
		Mesh->SetOwnerNoSee(false);
	}
}

FName AFPSCharacter::GetWeaponAttachPoint() const
{
	return WeaponAttachPoint;
}

USkeletalMeshComponent* AFPSCharacter::GetSpecificPawnMesh(bool WantFirstPerson) const
{
	return FirstPersonMesh.Get();
}

void AFPSCharacter::EquipWeapon(AFPSWeapon * Weapon)
{
	if (!Weapon)
		return;

	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, TEXT("Weapon equipped."));
	}

	UnEquipWeapon();
	ActiveWeapon = Weapon;
	ActiveWeapon->OnEquip(this);

}

void AFPSCharacter::UnEquipWeapon()
{
	if (ActiveWeapon)
	{
		ActiveWeapon->OnUnEquip();
		ActiveWeapon = nullptr;
	}
}