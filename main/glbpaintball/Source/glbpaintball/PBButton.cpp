


#include "glbpaintball.h"
#include "PBButton.h"



APBButton::APBButton(const class FPostConstructInitializeProperties& PCIP)
	: Super(PCIP)
{
	// Create the root component (collision)
	BaseCollisionComponent = PCIP.CreateDefaultSubobject<USphereComponent>(this, TEXT("BaseSphereComponent"));
	RootComponent = BaseCollisionComponent;

	BaseCollisionComponent->OnComponentBeginOverlap.AddDynamic(this, &APBButton::OnOverlap);

	// Create static mesh
	ButtonMesh = PCIP.CreateDefaultSubobject<UStaticMeshComponent>(this, TEXT("ButtonMesh"));

	// Attach static mesh component to root component
	ButtonMesh->AttachTo(RootComponent);

	Action = true;
	Recyclable = false;
	Active = true;
}

void APBButton::Push()
{
	if (Target && Active)
	{
		Target->SetEnabled(Action);
		//Play Sound
		if (ActivateSound)
		{
			this->PlaySoundAtLocation(ActivateSound, GetActorLocation(), 0.5f, 1.f);
		}

		if (Recyclable)
		{
			Action = !Action;
		}
		else
		{
			Active = false;
		}
	}
}

void APBButton::OnOverlap(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{

}



