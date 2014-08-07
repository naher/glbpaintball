

#include "FPSProject.h"
#include "FPSDartboard.h"


AFPSDartboard::AFPSDartboard(const class FPostConstructInitializeProperties& PCIP)
	: Super(PCIP)
{

}

void AFPSDartboard::OnHit(AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	Super::OnHit(OtherActor, OtherComp, NormalImpulse, Hit);

	Destroy();
}
