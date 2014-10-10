

#include "glbpaintball.h"
#include "PBAutomaticDoor.h"


APBAutomaticDoor::APBAutomaticDoor(const class FPostConstructInitializeProperties& PCIP)
	: Super(PCIP)
{

	BaseCollisionComponent = PCIP.CreateDefaultSubobject<UBoxComponent>(this, TEXT("BaseBoxComponent"));
	RootComponent = BaseCollisionComponent;
	// Create static mesh
	DoorMesh = PCIP.CreateDefaultSubobject<UStaticMeshComponent>(this, TEXT("DoorMesh"));

	BaseCollisionComponent->OnComponentBeginOverlap.AddDynamic(this, &APBAutomaticDoor::OnOverlap);
	BaseCollisionComponent->OnComponentEndOverlap.AddDynamic(this, &APBAutomaticDoor::OnEndOverlap);
	// Attach static mesh component to root component
	DoorMesh->AttachTo(RootComponent);
	Enabled = false;
}

void APBAutomaticDoor::BeginPlay()
{
	OriginalLocation = DoorMesh->GetComponentLocation();
}

bool APBAutomaticDoor::IsEnabled()
{
	return Enabled;
}

void APBAutomaticDoor::SetEnabled(bool enable)
{
	Enabled = enable;
}

void APBAutomaticDoor::OnEndOverlap(AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	CloseDoor();
}

void APBAutomaticDoor::OnOverlap(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	OpenDoor();
}

