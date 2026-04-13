// Kleith's Game

#include "PlanePlayerController.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "PlanePawn.h"

void APlanePlayerController::BeginPlay()
{
    Super::BeginPlay();

    CachedPlane = Cast<APlanePawn>(GetPawn());

    if (ULocalPlayer* LocalPlayer = GetLocalPlayer())
    {
        if (auto* Subsystem = LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>())
        {
            Subsystem->AddMappingContext(PlaneContext, 0);
        }
    }
}

void APlanePlayerController::SetupInputComponent()
{
    Super::SetupInputComponent();

    if (UEnhancedInputComponent* EIC = Cast<UEnhancedInputComponent>(InputComponent))
    {
        EIC->BindAction(IA_Throttle, ETriggerEvent::Triggered, this, &APlanePlayerController::HandleThrottle);
        EIC->BindAction(IA_Turn, ETriggerEvent::Triggered, this, &APlanePlayerController::HandleTurn);
        EIC->BindAction(IA_Look, ETriggerEvent::Triggered, this, &APlanePlayerController::HandleLook);

        EIC->BindAction(IA_MouseControl, ETriggerEvent::Started, this, &APlanePlayerController::MousePressed);
        EIC->BindAction(IA_MouseControl, ETriggerEvent::Completed, this, &APlanePlayerController::MouseReleased);
    }
}

void APlanePlayerController::HandleThrottle(const FInputActionValue& Value)
{
    if (CachedPlane)
        CachedPlane->SetThrottle(Value.Get<float>());
}

void APlanePlayerController::HandleTurn(const FInputActionValue& Value)
{
    if (CachedPlane)
        CachedPlane->SetYawInput(Value.Get<float>());
}

void APlanePlayerController::HandleLook(const FInputActionValue& Value)
{
    FVector2D Look = Value.Get<FVector2D>();

    if (CachedPlane)
    {
        CachedPlane->SetPitchInput(Look.Y);
        CachedPlane->SetRollInput(Look.X);
    }
}

void APlanePlayerController::MousePressed(const FInputActionValue& Value)
{
    if (CachedPlane)
        CachedPlane->SetMouseControl(true);
}

void APlanePlayerController::MouseReleased(const FInputActionValue& Value)
{
    if (CachedPlane)
        CachedPlane->SetMouseControl(false);
}