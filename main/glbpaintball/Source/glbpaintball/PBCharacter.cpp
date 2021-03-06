

#include "glbpaintball.h"
#include "PBWeapon.h"
#include "PBButton.h"
#include "PBGameMode.h"
#include "PBOnHitEffectsManager.h"
#include "PBCharacter.h"

APBCharacter::APBCharacter(const class FPostConstructInitializeProperties& PCIP)
	: Super(PCIP)
{
	
	
	// Start game in first person mode
	bIsFirstPersonCamera = true;

	// Create the root component (collision)
	BaseCollisionComponent = PCIP.CreateDefaultSubobject<USphereComponent>(this, TEXT("BaseSphereComponent"));
	BaseCollisionComponent->AttachTo(CapsuleComponent);
	BaseCollisionComponent->SetSphereRadius(200.f);
	// Create a CameraComponent 
	FirstPersonCameraComponent = PCIP.CreateDefaultSubobject<UCameraComponent>(this, TEXT("FirstPersonCamera"));
	FirstPersonCameraComponent->AttachParent = CapsuleComponent;

	// Position the camera a bit above the eyes
	FirstPersonCameraComponent->RelativeLocation = FVector(0, 0, 50.0f + BaseEyeHeight);

	// Setup Motion Blur
	FirstPersonCameraComponent->PostProcessSettings.MotionBlurAmount = 0.0f;
	FirstPersonCameraComponent->PostProcessSettings.MotionBlurMax = 0.8f;

	// Create a mesh component that will be used when being viewed from a '1st person' view (when controlling this pawn)
	FirstPersonMesh = PCIP.CreateDefaultSubobject<USkeletalMeshComponent>(this, TEXT("FirstPersonMesh"));
	FirstPersonMesh->SetOnlyOwnerSee(true);         // only the owning player will see this mesh
	FirstPersonMesh->AttachParent = FirstPersonCameraComponent;
	FirstPersonMesh->bCastDynamicShadow = false;
	FirstPersonMesh->CastShadow = false;

	// everyone but the owner can see the regular body mesh

	Mesh->SetOwnerNoSee(true);

	// Attach static mesh component to root component
	ActiveWeapon = nullptr;
}

void APBCharacter::BeginPlay()
{
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, TEXT("Using FPSCharacter"));
	}
	
	Inventory.AddZeroed(InventorySize);
	for (auto WeaponClass : DefaultInventoryClasses)
	{
		// Create new weapon and equip it
		FActorSpawnParameters SpawnInfo;
		SpawnInfo.bNoCollisionFail = true;
		APBWeapon* NewWeapon = GetWorld()->SpawnActor<APBWeapon>(WeaponClass, SpawnInfo);
		Inventory.Insert(NewWeapon, NewWeapon->GetSlotNumber());
	}

	GameMode = ((APBGameMode*)GetWorld()->GetAuthGameMode());

	/** Initial values for Energy and speed Variables*/
	EnergyLevel = 100.0f;
	NormalSpeedEnergy = EnergyLevel;
	SpeedFactorWalk = 9.5f;
	SpeedFactor = SpeedFactorWalk;
	SpeedFactorRun = 16.5f;
	BaseSpeed = 90.0f;
	Health = 100.0f;

	MaxEnergyLevel = 100;
	MinEnergyLevel = 50;

	EnergyDecayRateJump = 5;
	EnergyDecayRateWalk = 0.1;
	EnergyDecayRateRun = 0.15;
	EnergyDecayRate = EnergyDecayRateWalk;

	SetMovementStatus(ESM_Walking);
}

void APBCharacter::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	// set up gameplay key bindings
	InputComponent->BindAxis("MoveForward", this, &APBCharacter::MoveForward);
	InputComponent->BindAxis("MoveRight", this, &APBCharacter::MoveRight);
	InputComponent->BindAxis("Turn", this, &APBCharacter::AddControllerYawInput);
	InputComponent->BindAxis("LookUp", this, &APBCharacter::AddControllerPitchInput);
	InputComponent->BindAction("Jump", IE_Pressed, this, &APBCharacter::OnStartJump);
	InputComponent->BindAction("Jump", IE_Released, this, &APBCharacter::OnStopJump);
	InputComponent->BindAction("Change_Camera", IE_Pressed, this, &APBCharacter::OnCameraToggle);
	InputComponent->BindAction("Fire", IE_Pressed, this, &APBCharacter::OnFireStart);
	InputComponent->BindAction("Fire", IE_Released, this, &APBCharacter::OnFireEnd);
	InputComponent->BindAction("Run", IE_Pressed, this, &APBCharacter::OnRunStart);
	InputComponent->BindAction("Run", IE_Released, this, &APBCharacter::OnRunEnd);
	InputComponent->BindAction("Interact", IE_Pressed, this, &APBCharacter::Interact);
}

float APBCharacter::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent,
							   class AController* EventInstigator, class AActor* DamageCauser)
{
	EnergyLevel -= DamageAmount;

	if (EnergyLevel < 0.0f)
	{
		EnergyLevel = 0.0f;
	}

	if (OnHitEffectsManager)
	{
		OnHitEffectsManager->NotifyHit();
	}
	
	return DamageAmount;
}

void APBCharacter::ApplyWeaponRecoil()
{
	// try and play a firing animation if specified
	if (FireAnimation != NULL)
	{
		// Get the animation object for the arms mesh
		UAnimInstance* AnimInstance = FirstPersonMesh->GetAnimInstance();
		if (AnimInstance != NULL)
		{
			AnimInstance->Montage_Play(FireAnimation, 1.f);
		}
	}
}

void APBCharacter::UpdateAnimationMovementRate(float rate)
{
        // Get the animation object for the arms mesh
		UAnimInstance* AnimInstance = FirstPersonMesh->GetAnimInstance();
		
		if (AnimInstance != NULL)
		{
			FirstPersonMesh->GlobalAnimRateScale =  MovementStatus == ESM_Running ? (rate*1.5) : rate;
		}
}



float APBCharacter::GetEnergyLevel() const
{
	return EnergyLevel;
}

void APBCharacter::SetEnergyLevel(float NewEnergyLevel)
{
    EnergyLevel = NewEnergyLevel;
}

float APBCharacter::GetMaxEnergyLevel() const
{
	return MaxEnergyLevel;
}

void APBCharacter::SetMaxEnergyLevel(float NewMaxEnergyLevel)
{
  MaxEnergyLevel = NewMaxEnergyLevel;
}

float APBCharacter::GetMinEnergyLevel() const
{
	return MinEnergyLevel;
}

void APBCharacter::SetMinEnergyLevel(float NewMinEnergyLevel)
{
	EnergyLevel = NewMinEnergyLevel;
}

UCameraComponent * APBCharacter::GetCamera() const
{
	return FirstPersonCameraComponent.Get();
}

void APBCharacter::MoveForward(float Value)
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

void APBCharacter::MoveRight(float Value)
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

void APBCharacter::OnStartJump()
{
	if (!IsJumping())
	{
		if ((EnergyLevel - EnergyDecayRateJump) >= MinEnergyLevel)
		{
			bPressedJump = true;
			SetMovementStatus(ESM_Jumping);
		}
	}
}

void APBCharacter::OnStopJump()
{
	bPressedJump = false;
	SetMovementStatus(PrevMovementStatus);
}

void APBCharacter::OnFireStart()
{
	if (ActiveWeapon)
	{

		ActiveWeapon->OnTriggerPress();
		EventController->setAmmo(ActiveWeapon->GetAmmo());
	}
}

void APBCharacter::OnFireEnd()
{
	if (ActiveWeapon)
	{
		ActiveWeapon->OnTriggerRelease();
	}
}

void APBCharacter::OnPickUpAmmo()
{
	if (ActiveWeapon)
	{
		EventController->setAmmo(ActiveWeapon->GetAmmo());
	}
}

void APBCharacter::OnCameraToggle()
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

FName APBCharacter::GetWeaponAttachPoint() const
{
	return WeaponAttachPoint;
}

USkeletalMeshComponent* APBCharacter::GetSpecificPawnMesh(bool WantFirstPerson) const
{
	return FirstPersonMesh.Get();
}

void APBCharacter::EquipWeapon(APBWeapon * Weapon)
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

	EventController->setWeaponIcon(ActiveWeapon->GetIcon());
	EventController->setMaxAmmo(ActiveWeapon->GetMaxAmmo());
	EventController->setAmmo(ActiveWeapon->GetAmmo());
}

void APBCharacter::UnEquipWeapon()
{
	if (ActiveWeapon)
	{
		ActiveWeapon->OnUnEquip();
		ActiveWeapon = nullptr;

		EventController->releaseWeapon();
	}
}

void APBCharacter::SetMovementStatus(int32 status)
{
	if (MovementStatus != ESM_Jumping || status != ESM_Jumping)
	  PrevMovementStatus = MovementStatus;

	MovementStatus = status;
	switch (status)
	{
	    case ESM_Walking:
		  SpeedFactor = SpeedFactorWalk;
		  // EnergyDecayRate = EnergyDecayRateWalk;
		   break;
    
		case ESM_Running:
			SpeedFactor = SpeedFactorRun;
			EnergyDecayRate = EnergyDecayRateRun;
			break;

		case ESM_Jumping:
			EnergyLevel -= EnergyDecayRateJump;
			break;
	}
}

bool APBCharacter::IsInMovement()
{
	return !GetVelocity().IsZero();
}

bool APBCharacter::IsRunning()
{
	return MovementStatus == ESM_Running;
}

void APBCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	float AnimationSpeedRate;
	float CurrentEnergy = IsRunning() ? EnergyLevel :NormalSpeedEnergy;

	CharacterMovement->MaxWalkSpeed = SpeedFactor * CurrentEnergy + BaseSpeed;
	AnimationSpeedRate = CurrentEnergy / 100;
	
	if (IsInMovement() && EnergyLevel > MinEnergyLevel && IsRunning())
	{
		SetEnergyLevel(FMath::FInterpTo(EnergyLevel, MinEnergyLevel, DeltaSeconds, EnergyDecayRate));
	}

	UpdateAnimationMovementRate(AnimationSpeedRate);

	EventController->setBarEnergy(EnergyLevel/100);
	GameMode->setBarEnergy(EnergyLevel);
}

bool APBCharacter::AddWeaponToInventory(APBWeapon * Weapon)
{
	if (Weapon)
	{
		if (Inventory.Num() > Weapon->GetSlotNumber() && !Inventory[Weapon->GetSlotNumber()])
		{
			Inventory.Insert(Weapon, Weapon->GetSlotNumber());
			EventController->setWeaponInventary(Weapon->GetIcon(), Weapon->GetSlotNumber());
			return true;
		}
	}

	return false;
}

APBWeapon * APBCharacter::GetWeapon(UClass * WeaponClass) const
{
	for (auto Weapon : Inventory)
	{
		if (Weapon && Weapon->GetClass() == WeaponClass)
		{
			return Weapon;
		}
	}
	return nullptr;
}

void APBCharacter::RechargeEnergy(float Energy)
{
	EnergyLevel += Energy;

	if (EnergyLevel > MaxEnergyLevel)
	{
		EnergyLevel = MaxEnergyLevel;
	}
}

void APBCharacter::registerEventController(IPBEventController * controller)
{
	EventController = controller;
}

void APBCharacter::SetOnHitEffectsManager(APBOnHitEffectsManager * Manager)
{
	OnHitEffectsManager = Manager;
}

void APBCharacter::OnRunStart()
{
	if (EnergyLevel > MinEnergyLevel)
  	 SetMovementStatus(ESM_Running);

	// Enable Motion Blur
	FirstPersonCameraComponent->PostProcessSettings.MotionBlurAmount = 0.8f;
}

void APBCharacter::OnRunEnd()
{
	SetMovementStatus(ESM_Walking);

	// Disable Motion Blur
	FirstPersonCameraComponent->PostProcessSettings.MotionBlurAmount = 0.0f;
}

void APBCharacter::Interact()
{
	TArray<AActor*> collectedActors;
	if (BaseCollisionComponent)
	{
		BaseCollisionComponent->GetOverlappingActors(collectedActors);
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::SanitizeFloat(collectedActors.Num()));
		for (int32 iCollected = 0; iCollected < collectedActors.Num(); iCollected++)
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Pusshing"));
			APBButton * const button = Cast<APBButton>(collectedActors[iCollected]);

			if (button)
				button->Push();
		}
	}
}