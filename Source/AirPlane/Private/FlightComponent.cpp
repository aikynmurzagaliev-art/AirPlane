#include "FlightComponent.h"
#include "Components/StaticMeshComponent.h"

void UFlightComponent::Initialize(UStaticMeshComponent* InMesh)
{
    PlaneMesh = InMesh;
}

void UFlightComponent::TickComponent(float DeltaTime)
{
    if (!PlaneMesh) return;

    float TargetThrottle = FMath::Clamp(ThrottleInput, MaxReverseThrottle, MaxForwardThrottle);

    float InterpSpeed = (FMath::Abs(TargetThrottle) > 0.01f)
        ? ThrottleAcceleration
        : ThrottleDeceleration;

    CurrentThrottle = FMath::FInterpTo(CurrentThrottle, TargetThrottle, DeltaTime, InterpSpeed);

    ApplyForces(DeltaTime);
    ApplyRotation(DeltaTime);
}

void UFlightComponent::SetThrottle(float Value) { ThrottleInput = Value; }
void UFlightComponent::SetYawInput(float Value) { YawInput = Value; }
void UFlightComponent::SetPitchInput(float Value) { PitchInput = Value; }
void UFlightComponent::SetRollInput(float Value) { RollInput = Value; }
void UFlightComponent::SetMouseControl(bool bEnabled) { bMouseControl = bEnabled; }

void UFlightComponent::ApplyForces(float DeltaTime)
{
    FVector Forward = GetOwner()->GetActorForwardVector();
    FVector Velocity = PlaneMesh->GetComponentVelocity();
    float Speed = Velocity.Size();

    FVector Thrust;

    if (CurrentThrottle >= 0)
        Thrust = Forward * CurrentThrottle * ThrustPower;
    else
        Thrust = Forward * CurrentThrottle * ThrustPower * 0.3f;

    PlaneMesh->AddForce(Thrust);

    if (Speed < 10.f) return;

    FVector VelDir = Velocity.GetSafeNormal();

    float LiftStrength = Speed * Speed * LiftMultiplier;

    float ForwardDot = FVector::DotProduct(Forward, VelDir);
    ForwardDot = FMath::Clamp(ForwardDot, -1.f, 1.f);

    float AoA = FMath::RadiansToDegrees(FMath::Acos(ForwardDot));
    float LiftFactor = FMath::Sin(FMath::DegreesToRadians(AoA));

    if (FMath::Abs(AoA) > StallAngle)
        LiftFactor *= StallPenalty;

    if (Speed > MinSpeedForLift)
    {
        FVector Lift = GetOwner()->GetActorUpVector() * LiftStrength * LiftFactor;
        PlaneMesh->AddForce(Lift);
    }

    FVector Drag = -VelDir * Speed * Speed * DragCoefficient;
    PlaneMesh->AddForce(Drag);
}

void UFlightComponent::ApplyRotation(float DeltaTime)
{
    FVector Forward = GetOwner()->GetActorForwardVector();
    FVector Right = GetOwner()->GetActorRightVector();
    FVector Up = GetOwner()->GetActorUpVector();

   
   PlaneMesh->AddTorqueInRadians(Right * (PitchInput * PitchSpeed * TorqueStrength));
   PlaneMesh->AddTorqueInRadians(Forward * (RollInput * RollSpeed * TorqueStrength));

   FVector AutoYaw = Up * (RollInput * AutoYawStrength * TorqueStrength);
   PlaneMesh->AddTorqueInRadians(AutoYaw);
        
   PlaneMesh->AddTorqueInRadians(Up * (YawInput * TurnSpeed * TorqueStrength));
    
}