

#include "glbpaintball.h"
#include "PBCharacter.h"
#include "PBPickUp.h"


APBPickUp::APBPickUp(const class FPostConstructInitializeProperties& PCIP)
	: Super(PCIP)
{
	// Create the root component (collision)
	BaseCollisionComponent = PCIP.CreateDefaultSubobject<USphereComponent>(this, TEXT("BaseSphereComponent"));

	RootComponent = BaseCollisionComponent;

	// Create static mesh
	PickUpMesh = PCIP.CreateDefaultSubobject<UStaticMeshComponent>(this, TEXT("PickupMesh"));
	PickUpMesh->OnComponentHit.AddDynamic(this, &APBPickUp::OnHit);

	// Attach static mesh component to root component
	PickUpMesh->AttachTo(RootComponent);
}

void APBPickUp::OnPickedUp_Implementation(APBCharacter * Character) PURE_VIRTUAL(APBPickUp::OnPickedUp_Implementation, );

void APBPickUp::OnHit(AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	APBCharacter * Character = Cast<APBCharacter>(OtherActor);

	if (Character)
	{
		OnPickedUp(Character);
		Destroy();
	}
}