// Kleith's Game

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "FlightComponent.generated.h"

class UStaticMeshComponent;

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class AIRPLANE_API UFlightComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    UFlightComponent();
    void Initialize(UStaticMeshComponent* InMesh);

    virtual void TickComponent(
        float DeltaTime,
        ELevelTick TickType,
        FActorComponentTickFunction* ThisTickFunction
    ) override;

    void SetThrottle(float Value);
    void SetYawInput(float Value);
    void SetPitchInput(float Value);
    void SetRollInput(float Value);
    void SetMouseControl(bool bEnabled);

private:

    UStaticMeshComponent* PlaneMesh;

    float ThrottleInput;
    float YawInput;
    float PitchInput;
    float RollInput;

    bool bMouseControl;

    float CurrentThrottle = 0.f;
    float ThrottleAcceleration = 1.5f;
    float ThrottleDeceleration = 2.0f;

    float MaxForwardThrottle = 1.0f;
    float MaxReverseThrottle = -0.3f;


    float ThrustPower = 300000.0f;
    float TurnSpeed = 60.0f;
    float PitchSpeed = 80.0f;
    float RollSpeed = 120.0f;
    float AutoYawStrength = 40.0f;

    float LiftMultiplier = 0.05f;
    float DragCoefficient = 0.5f;
    float StallAngle = 25.0f;
    float StallPenalty = 0.3f;
    float MinSpeedForLift = 300.f;
    float TorqueStrength = 500.f;

private:
    void ApplyForces(float DeltaTime);
    void ApplyRotation(float DeltaTime);
};