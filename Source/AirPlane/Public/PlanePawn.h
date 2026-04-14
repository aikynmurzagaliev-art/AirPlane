// Kleith's Game

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "PlanePawn.generated.h"

class UStaticMeshComponent;
class UFlightComponent;
class USpringArmComponent;
class UCameraComponent;

UCLASS()
class AIRPLANE_API APlanePawn : public APawn
{
    GENERATED_BODY()

public:
    APlanePawn();

    virtual void Tick(float DeltaTime) override;
    virtual void BeginPlay() override;

    void Look(const FVector2D& LookAxis);
    void StartCameraReset();

    void SetThrottle(float Value);
    void SetYawInput(float Value);
    void SetPitchInput(float Value);
    void SetRollInput(float Value);
    void SetMouseControl(bool bEnabled);

private:
    UPROPERTY(VisibleAnywhere)
    UCameraComponent* Camera;

    UPROPERTY(VisibleAnywhere)
    USpringArmComponent* SpringArm;

    UPROPERTY(VisibleAnywhere)
    UStaticMeshComponent* PlaneMesh;

    UPROPERTY(VisibleAnywhere)
    UFlightComponent* FlightComponent;

    FRotator DefaultCameraRotation;
    bool bReturningCamera = false;
};