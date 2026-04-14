// Kleith's Game

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "WeaponComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class AIRPLANE_API UWeaponComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UWeaponComponent();
	void Initialize(UStaticMeshComponent* InMesh, USceneComponent* InMuzzlePoint);

	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	FActorComponentTickFunction* ThisTickFunction) override;

	virtual void BeginPlay() override;

	void Fire();
protected:

	UStaticMeshComponent* PlaneMesh;
	USceneComponent* MuzzlePoint;

	UPROPERTY(EditAnywhere, Category = "Weapon")
	float Damage = 20.f;
};
