// Kleith's Game

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "PlanePawn.generated.h"

class UStaticMeshComponent;

UCLASS()
class AIRPLANE_API APlanePawn : public APawn
{
    GENERATED_BODY()

public:
    APlanePawn();

    virtual void Tick(float DeltaTime) override;
    virtual void BeginPlay() override;

    void SetThrottle(float Value);
    void SetYawInput(float Value);
    void SetPitchInput(float Value);
    void SetRollInput(float Value);
    void SetMouseControl(bool bEnabled);

protected:

    UPROPERTY(VisibleAnywhere)
    UStaticMeshComponent* PlaneMesh;


    float ThrottleInput;
    float YawInput;
    float PitchInput;
    float RollInput;

    bool bMouseControl;


    UPROPERTY(EditAnywhere, Category = "Flight")
    float ThrustPower = 50000.0f;

    UPROPERTY(EditAnywhere, Category = "Flight")
    float TurnSpeed = 60.0f;

    UPROPERTY(EditAnywhere, Category = "Flight")
    float PitchSpeed = 80.0f;

    UPROPERTY(EditAnywhere, Category = "Flight")
    float RollSpeed = 120.0f;

    UPROPERTY(EditAnywhere, Category = "Flight")
    float AutoYawStrength = 40.0f;

    UPROPERTY(EditAnywhere, Category = "Flight|Physics")
    float LiftMultiplier = 0.05f;

    UPROPERTY(EditAnywhere, Category = "Flight|Physics")
    float DragCoefficient = 0.5f;

    UPROPERTY(EditAnywhere, Category = "Flight|Physics")
    float StallAngle = 25.0f;

    UPROPERTY(EditAnywhere, Category = "Flight|Physics")
    float StallPenalty = 0.3f;

    UPROPERTY(EditAnywhere, Category = "Flight|Physics")
    float MinSpeedForLift = 300.f;

    UPROPERTY(EditAnywhere, Category = "Flight|Physics")
    float TorqueStrength = 500.f;

    //acceleration
    float CurrentThrottle = 0.f;
    float ThrottleAcceleration = 1.5f;
    float ThrottleDeceleration = 2.0f;

    float MaxForwardThrottle = 1.0f;
    float MaxReverseThrottle = -0.3f;

private:

    void ApplyForces(float DeltaTime);
    void ApplyRotation(float DeltaTime);
};