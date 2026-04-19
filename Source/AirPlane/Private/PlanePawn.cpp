// Kleith's Game

#include "PlanePawn.h"
#include "Components/StaticMeshComponent.h"
#include "FlightComponent.h"
#include "WeaponComponent.h"
#include "HealthComponent.h"
#include "GameFramework\SpringArmComponent.h"
#include "Camera/CameraComponent.h"

APlanePawn::APlanePawn()
{
    PrimaryActorTick.bCanEverTick = true;

    bUseControllerRotationYaw = false;
    bUseControllerRotationPitch = false;
    bUseControllerRotationRoll = false;

    PlaneMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PlaneMesh"));
    RootComponent = PlaneMesh;

    PlaneMesh->SetSimulatePhysics(true);
    PlaneMesh->SetEnableGravity(true);
    PlaneMesh->SetAngularDamping(2.0f);
    PlaneMesh->SetLinearDamping(0.2f);

    FlightComponent = CreateDefaultSubobject<UFlightComponent>(TEXT("FlightComponent"));
    WeaponComponent = CreateDefaultSubobject<UWeaponComponent>(TEXT("WeaponComponent"));
    HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("HealthComponent"));

    LeftMuzzle = CreateDefaultSubobject<USceneComponent>(TEXT("LeftMuzzle"));
    LeftMuzzle->SetupAttachment(PlaneMesh);

    RightMuzzle = CreateDefaultSubobject<USceneComponent>(TEXT("RightMuzzle"));
    RightMuzzle->SetupAttachment(PlaneMesh);

    SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
    SpringArm->SetupAttachment(RootComponent);
    SpringArm->TargetArmLength = 300.f;
    SpringArm->bUsePawnControlRotation = true;

    Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
    Camera->SetupAttachment(SpringArm);
    Camera->bUsePawnControlRotation = false;
}

void APlanePawn::BeginPlay()
{
    Super::BeginPlay();

    FlightComponent->Initialize(PlaneMesh);
    WeaponComponent->Initialize(PlaneMesh, {LeftMuzzle, RightMuzzle});
    
}

void APlanePawn::Look(const FVector2D& LookAxis)
{
    AddControllerYawInput(LookAxis.X);
    AddControllerPitchInput(LookAxis.Y);
}

void APlanePawn::StartCameraReset()
{
    bReturningCamera = true;
    
}

void APlanePawn::StopCameraReset()
{
    bReturningCamera = false;
}

void APlanePawn::FallowingCamera(float DeltaTime)
{
    if (AController* MyController = GetController())
    {
        FRotator Current = MyController->GetControlRotation();
        FRotator Target = GetActorRotation();
        FRotator NewRot = FMath::RInterpTo(Current, Target, DeltaTime, 5.f);

        MyController->SetControlRotation(NewRot);
    }
}

void APlanePawn::ResetViewOfCamera(float DeltaTime)
{
    FVector Velocity = GetVelocity();
    float Speed = Velocity.Size();

    float SpeedAlpha = FMath::Clamp(Speed / MaxSpeedForFOV, 0.f, 1.f);

    float TargetFOV = FMath::Lerp(MinFOV, MaxFOV, SpeedAlpha);

    float NewFOV = FMath::FInterpTo(Camera->FieldOfView, TargetFOV, DeltaTime, 5.f);

    Camera->SetFieldOfView(NewFOV);
}

//void APlanePawn::ReturnCameraToHorizon(float DeltaTime)
//{
//    FRotator Current = SpringArm->GetComponentRotation();
//    FRotator PlaneRot = GetActorRotation();
//
//    
//    FRotator Target = FRotator(
//        PlaneRot.Pitch,
//        PlaneRot.Yaw,
//        0.f
//    );
//
//    FRotator NewRot = FMath::RInterpTo(Current, Target, DeltaTime, 2.0f);
//
//    SpringArm->SetWorldRotation(NewRot);
//}

void APlanePawn::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    
    if (bReturningCamera)
    {
        FallowingCamera(DeltaTime);
    }

    ResetViewOfCamera(DeltaTime);

    /*if(bHorizonCamera)
    {
        ReturnCameraToHorizon(DeltaTime);
    }*/
}

void APlanePawn::SetThrottle(float Value)
{
    FlightComponent->SetThrottle(Value);
}

void APlanePawn::SetYawInput(float Value)
{
    FlightComponent->SetYawInput(Value);
}

void APlanePawn::SetPitchInput(float Value)
{
    FlightComponent->SetPitchInput(Value);
}

void APlanePawn::SetRollInput(float Value)
{
    FlightComponent->SetRollInput(Value);
}

void APlanePawn::SetMouseControl(bool bEnabled)
{
    FlightComponent->SetMouseControl(bEnabled);
}

void APlanePawn::StartFireInput()
{
    WeaponComponent->StartFire();
}

void APlanePawn::StopFireInput()
{
    WeaponComponent->StopFire();
}

void APlanePawn::SteerTowards(FVector Target)
{

}
