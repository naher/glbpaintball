

#include "glbpaintball.h"
#include "PBObjective.h"


APBObjective::APBObjective(const class FPostConstructInitializeProperties& PCIP)
	: Super(PCIP)
{
	// Create the root component (collision)
	BaseCollisionComponent = PCIP.CreateDefaultSubobject<USphereComponent>(this, TEXT("BaseSphereComponent"));
	BaseCollisionComponent->OnComponentHit.AddDynamic(this, &APBObjective::OnHit);
	RootComponent = BaseCollisionComponent;

	// Create static mesh
	ObjectiveMesh = PCIP.CreateDefaultSubobject<UStaticMeshComponent>(this, TEXT("PickupMesh"));

	// Attach static mesh component to root component
	ObjectiveMesh->AttachTo(RootComponent);
}


