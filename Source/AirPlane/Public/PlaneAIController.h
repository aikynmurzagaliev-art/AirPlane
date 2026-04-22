// Kleith's Game

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "PlaneAIController.generated.h"

class UBehaviorTreeComponent;
class UBlackboardComponent;
class UBehaviorTree;

UCLASS()
class AIRPLANE_API APlaneAIController : public AAIController
{
	GENERATED_BODY()

protected:
	UPROPERTY()
	UBehaviorTreeComponent* BehaviorComp;

	UPROPERTY()
	UBlackboardComponent* BlackboardComp;

	UPROPERTY(EditDefaultsOnly)
	UBehaviorTree* BehaviorTreeAsset;

	virtual void OnPossess(APawn* InPawn) override;
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	
public:
	UPROPERTY()
	FVector TargetLocation;
};
