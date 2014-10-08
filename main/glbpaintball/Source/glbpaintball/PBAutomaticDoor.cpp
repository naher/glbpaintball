

#include "glbpaintball.h"
#include "PBAutomaticDoor.h"


APBAutomaticDoor::APBAutomaticDoor(const class FPostConstructInitializeProperties& PCIP)
	: Super(PCIP)
{
	// Create static mesh
	DoorMesh = PCIP.CreateDefaultSubobject<UStaticMeshComponent>(this, TEXT("DoorMesh"));
	DoorMesh->OnComponentBeginOverlap.AddDynamic(this, &APBAutomaticDoor::OnOverlap);
	DoorMesh->OnComponentEndOverlap.AddDynamic(this, &APBAutomaticDoor::OnEndOverlap);

	Enabled = false;
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

}

void APBAutomaticDoor::OnOverlap(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{

}

