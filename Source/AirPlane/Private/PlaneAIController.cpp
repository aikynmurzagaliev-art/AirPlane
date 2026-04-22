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
}

void APlaneAIController::Tick(float DeltaTime)
{
}

