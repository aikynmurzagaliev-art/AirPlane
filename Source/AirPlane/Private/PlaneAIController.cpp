// Kleith's Game


#include "PlaneAIController.h"
#include "PlanePawn.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTreeComponent.h"

void APlaneAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	if (BehaviorTreeAsset)
	{
		UseBlackboard(BehaviorTreeAsset->BlackboardAsset, BlackboardComp);

		RunBehaviorTree(BehaviorTreeAsset);
	}
}

void APlaneAIController::BeginPlay()
{
	Super::BeginPlay();

	SetActorTickEnabled(true);
	TargetLocation = FVector(0, 0, 1000);
}

void APlaneAIController::Tick(float DeltaTime)
{
	APlanePawn* PlanePawn = Cast<APlanePawn>(GetPawn());
	if (!PlanePawn) return;

}

