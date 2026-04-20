// Kleith's Game

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Projectile.generated.h"

class UProjectileMovementComponent;

UCLASS()
class AIRPLANE_API AProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	AProjectile();

protected:
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnHit(
		UPrimitiveComponent* HitComp,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		FVector NormalImpulse,
		const FHitResult& Hit
	);

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* Mesh;

	UPROPERTY(VisibleAnywhere)
	UProjectileMovementComponent* Movement;


	UPROPERTY(EditAnywhere, Category = "BulletSettings")
	float Speed = 20000.f;

	UPROPERTY(EditAnywhere, Category = "BulletSettings")
	float Damage = 20.f;

	UPROPERTY(EditAnywhere, Category = "BulletSettings")
	float LifeTime = 3.f;

public:	
	virtual void Tick(float DeltaTime) override;

};
