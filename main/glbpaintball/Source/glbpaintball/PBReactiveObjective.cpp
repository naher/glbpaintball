

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
	}
}

void APBReactiveObjective::FaceAndRotateToPoint(FVector point, float deltaSeconds)
{
	FRotator playerRot = FRotationMatrix::MakeFromX(point - this->GetActorLocation()).Rotator();
	playerRot.Pitch = GetActorRotation().Pitch;
	playerRot.Roll = GetActorRotation().Roll;
	playerRot.Yaw -= 90;
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
 
  if (this->Status == ES_Vigilance)
  {
	  
	  FRotator newRot(0, 0, 0);
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
  }
  else if (this->Status == ES_Attack)
  {
	  FVector playerLoc = ActiveCharacter->GetActorLocation();
	  FaceAndRotateToPoint(playerLoc, DeltaSeconds);
	  if (Weapon)
	  {
		  Weapon->OnTriggerPress();
	  }
  }
}

void APBReactiveObjective::OnEndOverlap(AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (Cast<APBCharacter>(OtherActor) != nullptr)
	{
		this->Status = ES_Vigilance;
		ActiveCharacter = nullptr;
	}
}

void APBReactiveObjective::OnOverlap(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	ActiveCharacter = Cast<APBCharacter>(OtherActor);

	if (ActiveCharacter != nullptr)
	{
		this->Status = ES_Attack;
	}
}
