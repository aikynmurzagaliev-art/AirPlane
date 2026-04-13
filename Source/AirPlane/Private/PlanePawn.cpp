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

    PlaneMesh->SetAngularDamping(2.0f);
    PlaneMesh->SetLinearDamping(0.2f);

    ThrottleInput = 0.f;
    YawInput = 0.f;
    PitchInput = 0.f;
    RollInput = 0.f;
    bMouseControl = false;
}

void APlanePawn::BeginPlay()
{
    Super::BeginPlay();
}

void APlanePawn::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    float TargetThrottle = ThrottleInput;

    
    TargetThrottle = FMath::Clamp(TargetThrottle, MaxReverseThrottle, MaxForwardThrottle);

    
    float InterpSpeed = (FMath::Abs(TargetThrottle) > 0.01f)
        ? ThrottleAcceleration
        : ThrottleDeceleration;

    CurrentThrottle = FMath::FInterpTo(
        CurrentThrottle,
        TargetThrottle,
        DeltaTime,
        InterpSpeed
    );

    ApplyForces(DeltaTime);
    ApplyRotation(DeltaTime);
}



void APlanePawn::SetThrottle(float Value)
{
    ThrottleInput = FMath::Clamp(Value, -1.f, 1.f);
}

void APlanePawn::SetYawInput(float Value) { YawInput = Value; }
void APlanePawn::SetPitchInput(float Value) { PitchInput = Value; }
void APlanePawn::SetRollInput(float Value) { RollInput = Value; }
void APlanePawn::SetMouseControl(bool bEnabled) { bMouseControl = bEnabled; }



void APlanePawn::ApplyForces(float DeltaTime)
{
    FVector Forward = GetActorForwardVector();
    FVector Velocity = PlaneMesh->GetComponentVelocity();

    float Speed = Velocity.Size();


    FVector Thrust;

    if (CurrentThrottle >= 0)
    {
        Thrust = GetActorForwardVector() * CurrentThrottle * ThrustPower;
    }
    else
    {
        Thrust = GetActorForwardVector() * CurrentThrottle * ThrustPower * 0.3f; // reverse
    }
    PlaneMesh->AddForce(Thrust);

    if (Speed < 10.f) return;

    FVector VelDir = Velocity.GetSafeNormal();

    float LiftStrength = Speed * Speed * LiftMultiplier;

    float ForwardDot = FVector::DotProduct(Forward, VelDir);
    ForwardDot = FMath::Clamp(ForwardDot, -1.f, 1.f);

    float AoA = FMath::RadiansToDegrees(FMath::Acos(ForwardDot));

    float LiftFactor = FMath::Sin(FMath::DegreesToRadians(AoA));

    if (FMath::Abs(AoA) > StallAngle)
    {
        LiftFactor *= StallPenalty;
    }

    if (Speed > MinSpeedForLift)
    {
        FVector Lift = GetActorUpVector() * LiftStrength * LiftFactor;
        PlaneMesh->AddForce(Lift);
    }


    FVector Drag = -VelDir * Speed * Speed * DragCoefficient;
    PlaneMesh->AddForce(Drag);
}



void APlanePawn::ApplyRotation(float DeltaTime)
{
    FVector Forward = GetActorForwardVector();
    FVector Right = GetActorRightVector();
    FVector Up = GetActorUpVector();

    if (bMouseControl)
    {

        FVector PitchTorque = Right * (PitchInput * PitchSpeed * TorqueStrength);
        FVector RollTorque = Forward * (RollInput * RollSpeed * TorqueStrength);

        PlaneMesh->AddTorqueInRadians(PitchTorque);
        PlaneMesh->AddTorqueInRadians(RollTorque);


        FVector AutoYaw = Up * (RollInput * AutoYawStrength * TorqueStrength);
        PlaneMesh->AddTorqueInRadians(AutoYaw);
    }
    else
    {

        FVector YawTorque = Up * (YawInput * TurnSpeed * TorqueStrength);
        PlaneMesh->AddTorqueInRadians(YawTorque);
    }
}