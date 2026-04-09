// Kleith's Game


#include "PlanePawn.h"
#include "Components/StaticMeshComponent.h"

APlanePawn::APlanePawn()
{
    PrimaryActorTick.bCanEverTick = true;

    PlaneMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PlaneMesh"));
    RootComponent = PlaneMesh;

    PlaneMesh->SetSimulatePhysics(true);
    PlaneMesh->SetEnableGravity(false);

    ThrottleInput = 0.f;
    YawInput = 0.f;
    PitchInput = 0.f;
    bMouseControl = false;
}

void APlanePawn::BeginPlay()
{
    Super::BeginPlay();
}

void APlanePawn::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    ApplyForces(DeltaTime);
    ApplyRotation(DeltaTime);
}


void APlanePawn::SetThrottle(float Value)
{
    ThrottleInput = Value;
}

void APlanePawn::SetYawInput(float Value)
{
    YawInput = Value;
}

void APlanePawn::SetPitchInput(float Value)
{
    PitchInput = Value;
}

void APlanePawn::SetMouseControl(bool bEnabled)
{
    bMouseControl = bEnabled;
}

//physic

void APlanePawn::ApplyForces(float DeltaTime)
{
    FVector Forward = GetActorForwardVector();
    FVector Velocity = PlaneMesh->GetComponentVelocity();

    float Speed = Velocity.Size();

    
    FVector Thrust = Forward * ThrottleInput * ThrustPower;
    PlaneMesh->AddForce(Thrust);

    
    float LiftForce = Speed * LiftCoefficient;
    FVector Lift = FVector::UpVector * LiftForce;

    PlaneMesh->AddForce(Lift);
}

void APlanePawn::ApplyRotation(float DeltaTime)
{
    
    float Yaw = YawInput * TurnSpeed * DeltaTime;

    
    float Pitch = 0.f;
    if (bMouseControl)
    {
        Pitch = PitchInput * PitchSpeed * DeltaTime;
    }

    FRotator DeltaRot = FRotator(Pitch, Yaw, 0.f);
    PlaneMesh->AddLocalRotation(DeltaRot);
}

