

#include "glbpaintball.h"
#include "Kismet/KismetMathLibrary.h"
#include "PBWeapon.h"
#include "PBReactiveObjective.h"


APBReactiveObjective::APBReactiveObjective(const class FPostConstructInitializeProperties& PCIP)
	: Super(PCIP)
{
	PrimaryActorTick.bCanEverTick = true;
	Status = ES_Vigilance;
	BaseCollisionComponent->OnComponentBeginOverlap.AddDynamic(this, &APBReactiveObjective::OnOverlap);
	BaseCollisionComponent->OnComponentEndOverlap.AddDynamic(this, &APBReactiveObjective::OnEndOverlap);
	
	float minDifferenceBetweenAngles = 30;
	float minRotationAngle = this->GetActorRotation().Yaw;

	//MinRotator.Yaw = (this->GetActorRotation().Yaw / 2) * (-1);
	//MaxRotator.Yaw = this->GetActorRotation().Yaw / 2;

	RotationSpeed = 7;

	AudioCompStartAttack = PCIP.CreateDefaultSubobject<UAudioComponent>(this, TEXT("/Game/Audio/Enemies/Sentinel/AttackReady.wav"));
	if (AudioCompStartAttack)
	{
		AudioCompStartAttack->AttachParent = RootComponent;
		AudioCompStartAttack->bAutoActivate = false;
	}

	AttackDelay = 0.6;
}

void APBReactiveObjective::BeginPlay()
{
	DegreesToRotate = FMath::RandRange(0, 120);
	float minRotationAngle = this->GetActorRotation().Yaw;
	MinRotator.Yaw = minRotationAngle;
	MaxRotator.Yaw = minRotationAngle + DegreesToRotate;
	ActualRotator = MaxRotator;
	IsActualRotatorMax = true;

	PlayerCharacter = (*(GetWorld()->GetPlayerControllerIterator()))->GetPawn();

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

void APBReactiveObjective::FaceAndRotateToPoint(const FVector & point, float deltaSeconds, float error)
{
	FVector ErrorVector(error, error, error);
	FBox AimBox(point-ErrorVector, point+ErrorVector);

	FRotator playerRot = FRotationMatrix::MakeFromX(FMath::RandPointInBox(AimBox) - this->GetActorLocation()).Rotator();
	playerRot.Pitch = GetActorRotation().Pitch;
	playerRot.Roll = GetActorRotation().Roll;
	FRotator newRot = FMath::RInterpTo(this->GetActorRotation(), playerRot, deltaSeconds, 9);
	this->SetActorRotation(newRot);
}

void APBReactiveObjective::Tick(float DeltaSeconds)
{
  if (PlayerCharacter != NULL && MonitorPoint != NULL)
  {
	FVector PlayerToMonitor = MonitorPoint->GetActorLocation() - PlayerCharacter->GetActorLocation();

	// f(MaxDist)=0 = FromPoint.Location{
	float MovementRatio = 1 - FMath::Clamp<float>(PlayerToMonitor.Size(), MinDist, MaxDist) / MaxDist;
	
	FVector NewLocation = FMath::Lerp<FVector, float>(FromPoint->GetActorLocation(), ToPoint->GetActorLocation(), MovementRatio);

	SetActorLocation(NewLocation);
  }

  FRotator newRot(0, 0, 0);
  switch (Status)
  {
  case ES_Vigilance:
	  newRot = FMath::RInterpTo(this->GetActorRotation(), ActualRotator, DeltaSeconds, RotationSpeed);

	  this->SetActorRotation(newRot);
	  if (newRot.Yaw >= (MaxRotator.Yaw - 1) && IsActualRotatorMax)
	  {
		  ActualRotator = MinRotator;
		  IsActualRotatorMax = false;
	  }
	  else if (newRot.Yaw <= (MinRotator.Yaw + 1) && !IsActualRotatorMax)
	  {
		  ActualRotator = MaxRotator;
		  IsActualRotatorMax = true;
	  }

	  if (Weapon)
	  {
		  Weapon->OnTriggerRelease();
	  }
	  break;
  case ES_Attack:
	  FaceAndRotateToPoint(ActiveCharacter->GetActorLocation(), DeltaSeconds, ErrorMargin);
	  if (Weapon)
	  {
		  Weapon->OnTriggerPress();
	  }
	  break;
  }
}

void APBReactiveObjective::StartAtack()
{
	this->Status = ES_Attack;
}

void APBReactiveObjective::OnEndOverlap(AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (Cast<APBCharacter>(OtherActor) != nullptr)
	{
		this->Status = ES_Vigilance;
		ActiveCharacter = nullptr;
		GetWorldTimerManager().SetTimer(this, &APBReactiveObjective::StartAtack, -1, false);
	}
}

void APBReactiveObjective::OnOverlap(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	APBCharacter * CharOtherActor = Cast<APBCharacter>(OtherActor);

	if (CharOtherActor != nullptr)
	{
		//Play Sound
		if (AudioCompStartAttack)
		{
			AudioCompStartAttack->Activate(true);
			AudioCompStartAttack->Play(0.0f);
		}

		ActiveCharacter = CharOtherActor;
		GetWorldTimerManager().SetTimer(this, &APBReactiveObjective::StartAtack, 1, false);
	}
}
