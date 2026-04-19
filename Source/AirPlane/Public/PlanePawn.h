// Kleith's Game

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "PlanePawn.generated.h"

class UStaticMeshComponent;
class USpringArmComponent;
class UCameraComponent;

class UFlightComponent;
class UWeaponComponent;
class UHealthComponent;

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
    void StopCameraReset();
    void FallowingCamera(float DeltaTime);
    void ResetViewOfCamera(float DeltaTime);
    //void ReturnCameraToHorizon(float DeltaTime);

    void SetThrottle(float Value);
    void SetYawInput(float Value);
    void SetPitchInput(float Value);
    void SetRollInput(float Value);
    void SetMouseControl(bool bEnabled);
    void StartFireInput();
    void StopFireInput();

    //AI controller
    void SteerTowards(FVector Target);

private:
    //components
    UPROPERTY(VisibleAnywhere)
    UCameraComponent* Camera;

    UPROPERTY(VisibleAnywhere)
    USpringArmComponent* SpringArm;

    UPROPERTY(VisibleAnywhere)
    UStaticMeshComponent* PlaneMesh;

    UPROPERTY(VisibleAnywhere)
    UFlightComponent* FlightComponent;

    UPROPERTY(VisibleAnywhere)
    UWeaponComponent* WeaponComponent;

    UPROPERTY(VisibleAnywhere)
    UHealthComponent* HealthComponent;

    UPROPERTY(VisibleAnywhere)
    USceneComponent* LeftMuzzle;

    UPROPERTY(VisibleAnywhere)
    USceneComponent* RightMuzzle;


    //variables
     
    UPROPERTY(EditAnywhere, Category = "Camera")
    float MinFOV = 90.f;

    UPROPERTY(EditAnywhere, Category = "Camera")
    float MaxFOV = 110.f;

    UPROPERTY(EditAnywhere, Category = "Camera")
    float MaxSpeedForFOV = 6000.f;


    FRotator DefaultRotation;

    bool bReturningCamera = false;
    bool bHorizonCamera = false;

    
};