// Kleith's Game

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CombatTurret.generated.h"

class UWeaponComponent;
class UHealthComponent;
class USphereComponent;

UCLASS()
class AIRPLANE_API ACombatTurret : public AActor
{
	GENERATED_BODY()
	
public:	
	ACombatTurret();

protected:

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* Mesh;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* TurretMesh;

	UPROPERTY(VisibleAnywhere)
	USceneComponent* Muzzle;

	UPROPERTY(VisibleAnywhere)
	USphereComponent* DetectionSphere;

	UPROPERTY(VisibleAnywhere)
	UWeaponComponent* Weapon;

	UPROPERTY(VisibleAnywhere)
	UHealthComponent* Health;

	APawn* PlayerPawn;

	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;
	void RotateToTarget(float Deltatime);

	UFUNCTION()
	void OnOverlapBegin(
		UPrimitiveComponent* OverlappedComp,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult
	);

	UFUNCTION()
	void OnOverlapEnd(
		UPrimitiveComponent* OverlappedComp,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex
	);

	UPROPERTY(EditAnywhere, Category = "Combat")
	float DetectionRange = 2000.f;

	bool bPlayerDetected = false;

	UPROPERTY(EditAnywhere, Category = "Combat")
	float RotationSpeed = 5.f;


};
