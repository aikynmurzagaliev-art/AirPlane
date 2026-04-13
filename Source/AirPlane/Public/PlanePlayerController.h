// Kleith's Game

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "PlanePlayerController.generated.h"

class UInputMappingContext;
class UInputAction;
class APlanePawn;

UCLASS()
class AIRPLANE_API APlanePlayerController : public APlayerController
{
    GENERATED_BODY()

protected:
    virtual void BeginPlay() override;
    virtual void SetupInputComponent() override;

private:

    UPROPERTY(EditDefaultsOnly, Category = "Input")
    UInputMappingContext* PlaneContext;

    UPROPERTY(EditDefaultsOnly, Category = "Input")
    UInputAction* IA_Throttle;

    UPROPERTY(EditDefaultsOnly, Category = "Input")
    UInputAction* IA_Turn;

    UPROPERTY(EditDefaultsOnly, Category = "Input")
    UInputAction* IA_Look;

    UPROPERTY(EditDefaultsOnly, Category = "Input")
    UInputAction* IA_MouseControl;

    APlanePawn* CachedPlane;


    void HandleThrottle(const struct FInputActionValue& Value);
    void HandleTurn(const struct FInputActionValue& Value);
    void HandleLook(const struct FInputActionValue& Value);

    void MousePressed(const struct FInputActionValue& Value);
    void MouseReleased(const struct FInputActionValue& Value);
};