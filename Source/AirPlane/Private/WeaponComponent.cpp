// Kleith's Game

#include "WeaponComponent.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"

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
	for (USceneComponent* Muzzle : MuzzlePoints) 
	{
		if (!PlaneMesh) return;

		FVector Start = Muzzle->GetComponentLocation();
		FVector Direction = PlaneMesh->GetForwardVector();
		Direction = FMath::VRandCone(Direction, FMath::DegreesToRadians(Spread));

		FVector End = Start + Direction * 10000;

		//debug
		DrawDebugLine(
			GetWorld(),
			Start,
			End,
			FColor::Red,
			false,
			2.0f,
			0,
			2.0f
		);

		FHitResult Hit;
		GetWorld()->LineTraceSingleByChannel(Hit, Start, End, ECC_Visibility);

		if (Hit.bBlockingHit)
		{
			AActor* HitActor = Hit.GetActor();

			if (HitActor && HitActor != GetOwner())
			{
				UGameplayStatics::ApplyDamage(
					HitActor,
					Damage,
					GetOwner()->GetInstigatorController(),
					GetOwner(),
					UDamageType::StaticClass()
				);
			}
		}
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

