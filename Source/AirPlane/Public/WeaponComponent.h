// Kleith's Game

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "WeaponComponent.generated.h"

class AProjectile;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class AIRPLANE_API UWeaponComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UWeaponComponent();
	void Initialize(UStaticMeshComponent* InMesh, const TArray<USceneComponent*>& InMuzzles);

	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	FActorComponentTickFunction* ThisTickFunction) override;

	virtual void BeginPlay() override;

	void Fire();

	void StartFire();
	void StopFire();

protected:

	UStaticMeshComponent* PlaneMesh;
	TArray<USceneComponent*> MuzzlePoints;
	FTimerHandle FireTimer;

	UPROPERTY(EditAnywhere, Category = "Weapon")
	TSubclassOf<AProjectile> ProjectileClass;

	UPROPERTY(EditAnywhere, Category = "Weapon")
	USoundBase* FireSound;

	UPROPERTY(EditAnywhere, Category = "Weapon")
	float FireRate = 0.1f;

	UPROPERTY(EditAnywhere, Category = "Weapon")
	float Spread = 1.0f;

	bool bIsFiring = false;
};
