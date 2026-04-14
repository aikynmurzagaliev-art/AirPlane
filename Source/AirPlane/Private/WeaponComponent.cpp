// Kleith's Game

#include "WeaponComponent.h"
#include "Kismet/GameplayStatics.h"

UWeaponComponent::UWeaponComponent()
{
	
	PrimaryComponentTick.bCanEverTick = true;

	
}

void UWeaponComponent::Initialize(UStaticMeshComponent* InMesh, USceneComponent* InMuzzlePoint)
{
	PlaneMesh = InMesh;
	MuzzlePoint = InMuzzlePoint;
}

void UWeaponComponent::BeginPlay()
{
	Super::BeginPlay();

}

void UWeaponComponent::Fire()
{
	if (!PlaneMesh) return;

	FVector Start = MuzzlePoint->GetComponentLocation();
	FVector Direction = PlaneMesh->GetForwardVector();
	FVector End = Start + Direction * 10000;

	FHitResult Hit;
	GetWorld()->LineTraceSingleByChannel(Hit, Start, End, ECC_Visibility);

	if (Hit.bBlockingHit)
	{
		AActor* HitActor = Hit.GetActor();

		if(HitActor && HitActor != GetOwner())
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



void UWeaponComponent::TickComponent(
	float DeltaTime, 
	ELevelTick TickType, 
	FActorComponentTickFunction* ThisTickFunction
	)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);


}

