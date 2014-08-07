

#include "FPSProject.h"
#include "FPSObjective.h"


AFPSObjective::AFPSObjective(const class FPostConstructInitializeProperties& PCIP)
	: Super(PCIP)
{
	// Create the root component (collision)
	BaseCollisionComponent = PCIP.CreateDefaultSubobject<USphereComponent>(this, TEXT("BaseSphereComponent"));
	BaseCollisionComponent->OnComponentHit.AddDynamic(this, &AFPSObjective::OnHit);
	RootComponent = BaseCollisionComponent;

	// Create static mesh
	ObjectiveMesh = PCIP.CreateDefaultSubobject<UStaticMeshComponent>(this, TEXT("PickupMesh"));

	// Attach static mesh component to root component
	ObjectiveMesh->AttachTo(RootComponent);
}

void AFPSObjective::OnHit(AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{

}
