

#include "glbpaintball.h"
#include "PBCharacter.h"
#include "PBPickUp.h"


APBPickUp::APBPickUp(const class FPostConstructInitializeProperties& PCIP)
	: Super(PCIP)
{
	// Create static mesh
	PickUpMesh = PCIP.CreateDefaultSubobject<UStaticMeshComponent>(this, TEXT("PickupMesh"));
	PickUpMesh->OnComponentHit.AddDynamic(this, &APBPickUp::OnHit);
	PickUpMesh->BodyInstance.SetCollisionProfileName("PickUp");

	RootComponent = PickUpMesh;
}

bool APBPickUp::OnPickedUp_Implementation(APBCharacter * Character) PURE_VIRTUAL(APBPickUp::OnPickedUp_Implementation, return false;);

void APBPickUp::OnHit(AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	APBCharacter * Character = Cast<APBCharacter>(OtherActor);

	if (Character && OnPickedUp(Character))
	{
		Destroy();
	}
}