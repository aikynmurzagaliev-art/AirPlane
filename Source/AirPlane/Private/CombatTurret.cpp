// Kleith's Game


#include "CombatTurret.h"
#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"
#include "WeaponComponent.h"
#include "HealthComponent.h"

ACombatTurret::ACombatTurret()
{
	PrimaryActorTick.bCanEverTick = true;
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	RootComponent = Mesh;

	TurretMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TurretMesh"));
	TurretMesh->SetupAttachment(Mesh);

	Muzzle = CreateDefaultSubobject<USceneComponent>(TEXT("Muzzle"));
	Muzzle->SetupAttachment(TurretMesh);

	DetectionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("DetectionSphere"));
	DetectionSphere->SetupAttachment(Mesh);
	DetectionSphere->SetSphereRadius(DetectionRange);

	Weapon = CreateDefaultSubobject<UWeaponComponent>(TEXT("Weapon"));
	Health = CreateDefaultSubobject<UHealthComponent>(TEXT("Health"));
}

void ACombatTurret::BeginPlay()
{
	Super::BeginPlay();
	
	DetectionSphere->OnComponentBeginOverlap.AddDynamic(this, &ACombatTurret::OnOverlapBegin);
	DetectionSphere->OnComponentEndOverlap.AddDynamic(this, &ACombatTurret::OnOverlapEnd);

	PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);

	TArray<USceneComponent*> Muzzles;
	Muzzles.Add(Muzzle);
	Weapon->Initialize(Mesh, Muzzles);
}

void ACombatTurret::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bPlayerDetected && PlayerPawn)
	{
		RotateToTarget(DeltaTime);
		Weapon->StartFire();
	}
	else
	{
		Weapon->StopFire();
	}
}

void ACombatTurret::RotateToTarget(float DeltaTime)
{
	FVector Direction = PlayerPawn->GetActorLocation() - TurretMesh->GetComponentLocation();
	FRotator TargetRot = Direction.Rotation();

	FRotator CurrentRot = TurretMesh->GetComponentRotation();

	FRotator NewRot = FMath::RInterpTo(CurrentRot, TargetRot, DeltaTime, RotationSpeed);

	TurretMesh->SetWorldRotation(NewRot);
}

void ACombatTurret::OnOverlapBegin(
	UPrimitiveComponent* OverlappedComp, 
	AActor* OtherActor, 
	UPrimitiveComponent* OtherComp, 
	int32 OtherBodyIndex, 
	bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor == PlayerPawn)
	{
		bPlayerDetected = true;
	}
}

void ACombatTurret::OnOverlapEnd(
	UPrimitiveComponent* OverlappedComp, 
	AActor* OtherActor, 
	UPrimitiveComponent* OtherComp, 
	int32 OtherBodyIndex)
{
	if (OtherActor == PlayerPawn)
	{
		bPlayerDetected = false;
	}
}

