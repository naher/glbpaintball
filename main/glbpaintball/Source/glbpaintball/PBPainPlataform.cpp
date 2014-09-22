

#include "glbpaintball.h"
#include "PBPainPlataform.h"


APBPainPlataform::APBPainPlataform(const class FPostConstructInitializeProperties& PCIP)
	: Super(PCIP)
{
	// Create static mesh
	PainMesh = PCIP.CreateDefaultSubobject<UStaticMeshComponent>(this, TEXT("PainMesh"));
	PainMesh->OnComponentBeginOverlap.AddDynamic(this, &APBPainPlataform::OnOverlap);
	PainMesh->OnComponentEndOverlap.AddDynamic(this, &APBPainPlataform::StopInflictDamage);
	PainMesh->BodyInstance.SetCollisionProfileName("Pain");

	RootComponent = PainMesh;

	IsCausingDamage = false;
	DamageSeverity = 10;
	ActiveCharacter = nullptr;
}


void APBPainPlataform::InflictDamage()
{
	if (ActiveCharacter != nullptr)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::White, "Apply Damage");
		ActiveCharacter->ApplyDamage(DamageSeverity);
	}
}

void APBPainPlataform::StopInflictDamage(AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	ActiveCharacter = Cast<APBCharacter>(OtherActor);
	if (ActiveCharacter != nullptr)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, "Stop Damage");
		GetWorldTimerManager().SetTimer(this, &APBPainPlataform::InflictDamage, -1, false);
		IsCausingDamage = false;
	}
}

void APBPainPlataform::OnOverlap(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	ActiveCharacter = Cast<APBCharacter>(OtherActor);

	if (ActiveCharacter != nullptr && !IsCausingDamage)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, "Hit Plataform");
		InflictDamage();
		GetWorldTimerManager().SetTimer(this, &APBPainPlataform::InflictDamage, 1, true);
		IsCausingDamage = true;
	}
}




