

#pragma once

#include "PBWeaponHolder.h"
#include "PBObjective.h"
#include "GameFramework/Actor.h"
#include "PBCharacter.h"
#include "PBReactiveObjective.generated.h"

/**
 * 
 */
UENUM(BlueprintType) 
enum EnumStatus
{
 ES_Vigilance UMETA(DisplayName = "Vigilance"),
 ES_Attack UMETA(DisplayName = "Attack"),
 ES_PreparingAttack UMETA(DisplayName = "PreparingAttack"),
 ES_Dead UMETA(DisplayName = "Dead"),
};

UCLASS()
class GLBPAINTBALL_API APBReactiveObjective : public APBObjective, public IPBWeaponHolder
{
	GENERATED_UCLASS_BODY()

	/** Status of the Objective */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Status)
	int32 Status;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ActorRotation)
	float RotationSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ActorRotation)
	float DegreesToRotate;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Difficulty)
	float ErrorMargin;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AttackDelay)
	float AttackDelay;

	FRotator MinRotator;

	FRotator MaxRotator;

	FRotator ActualRotator;

	bool IsActualRotatorMax;

	/** AnimMontage to play each time we fire */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	class UAnimMontage* FireAnimation;

	UFUNCTION()
	virtual void Tick(float DeltaSeconds) override;

	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable, Category = Weapon)
	virtual void ApplyWeaponRecoil() override;

protected:

	/** Character hit the painPlataform*/
	UPROPERTY(VisibleAnywhere, Category = Damage)
	class APBCharacter * ActiveCharacter;

	/** Initial position of the objective's movement */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Movement)
	ATargetPoint* FromPoint;

	/** Final position of the objective's movement */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Movement)
	ATargetPoint* ToPoint;

	/** Point used as a reference to calculate distance */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Movement)
	ATargetPoint* MonitorPoint;

	/** Minimum distance from the monitor for the objective to react */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Movement)
	float MinDist;

	/** Maximum distance from the monitor for the objective to react */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Movement)
	float MaxDist;

	/** Weapon held by this objetive */
	UPROPERTY(EditAnywhere, Category = Weapon)
	TSubclassOf<class APBWeapon> WeaponClass;

	/** StartAttack Audio Component*/
	UPROPERTY(EditDefaultsOnly, Category = Audio)
	USoundCue *  SoundStartAttack;

	/** called when finish the overlap */
	UFUNCTION()
	void OnEndOverlap(AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	/** called up on collision */
	UFUNCTION()
	void OnOverlap(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

	/** Set the view to the character face **/
	UFUNCTION()
	void FaceAndRotateToPoint(const FVector & point, float deltaSeconds, float error);

	/** Set the view to the character face **/
	UFUNCTION()
	void StartAtack();


private:
	AActor * PlayerCharacter;

	APBWeapon * Weapon;
	
};
