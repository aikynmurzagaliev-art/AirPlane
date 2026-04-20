// Kleith's Game

#include "WeaponComponent.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"
#include "Projectile.h"

UWeaponComponent::UWeaponComponent()
{
	
	PrimaryComponentTick.bCanEverTick = true;

	
}

void UWeaponComponent::Initialize(UStaticMeshComponent* InMesh, const TArray<USceneComponent*>& InMuzzles)
{
	PlaneMesh = InMesh;
	MuzzlePoints = InMuzzles;
}

void UWeaponComponent::BeginPlay()
{
	Super::BeginPlay();

}

void UWeaponComponent::Fire()
{
	if (!ProjectileClass || !PlaneMesh) return;

	FActorSpawnParameters Params;
	Params.Owner = GetOwner();
	Params.Instigator = Cast<APawn>(GetOwner());

	for (USceneComponent* Muzzle : MuzzlePoints)
	{
		if (!Muzzle) continue;

		FVector Location = Muzzle->GetComponentLocation();
		FRotator Rotation = Muzzle->GetComponentRotation();

		GetWorld()->SpawnActor<AProjectile>(
			ProjectileClass,
			Location,
			Rotation,
			Params
		);
	}
}

void UWeaponComponent::StartFire()
{
	if (bIsFiring) return;

	bIsFiring = true;

	Fire();

	GetWorld()->GetTimerManager().SetTimer(
		FireTimer,
		this,
		&UWeaponComponent::Fire,
		FireRate,
		true
	);
}

void UWeaponComponent::StopFire()
{
	bIsFiring = false;

	GetWorld()->GetTimerManager().ClearTimer(FireTimer);
}



void UWeaponComponent::TickComponent(
	float DeltaTime, 
	ELevelTick TickType, 
	FActorComponentTickFunction* ThisTickFunction
	)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);


}

