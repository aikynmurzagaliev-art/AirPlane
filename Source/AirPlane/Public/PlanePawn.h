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
    void SetMouseControl(bool bEnabled);

protected:

    UPROPERTY(VisibleAnywhere)
    UStaticMeshComponent* PlaneMesh;

    float ThrottleInput;
    float YawInput;
    float PitchInput;
    bool bMouseControl;

    UPROPERTY(EditAnywhere, Category = "Flight")
    float ThrustPower = 500000.0f;

    UPROPERTY(EditAnywhere, Category = "Flight")
    float LiftCoefficient = 0.3f;

    UPROPERTY(EditAnywhere, Category = "Flight")
    float TurnSpeed = 60.0f;

    UPROPERTY(EditAnywhere, Category = "Flight")
    float PitchSpeed = 60.0f;

private:

    void ApplyForces(float DeltaTime);
    void ApplyRotation(float DeltaTime);
};