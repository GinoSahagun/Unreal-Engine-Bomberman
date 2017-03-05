// Fill out your copyright notice in the Description page of Project Settings.

#include "Bomber.h"
#include "BTTask_FindPatrolLocation.h"

/* AI Specific includes */
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyAllTypes.h"

/* AI Enemy Character Include*/
#include "EnemyCharacter.h"
#include "EnemyAIController.h"
#include "BomberCharacter.h"

EBTNodeResult::Type UBTTask_FindPatrolLocation::ExecuteTask(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory)
{
	AEnemyAIController* myController = Cast<AEnemyAIController>(OwnerComp.GetAIOwner());
	if (myController == nullptr)
	{
		return EBTNodeResult::Failed;
		GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Green, "Cant Get Controller");
	}
	ASBotWayPoint* current = myController->GetWaypoint();
	if (current)
	{
		/* Find a position that is close to the waypoint. We add a small random to this position to give build predictable patrol patterns  */
		const float SearchRadius = 200.0f;
		const FVector SearchOrigin = current->GetActorLocation();
		const FVector Loc = UNavigationSystem::GetRandomPointInNavigableRadius(myController, SearchOrigin, SearchRadius);
		if (Loc != FVector::ZeroVector)
		{
			/* The selected key should be "PatrolLocation" in the BehaviorTree setup */
			OwnerComp.GetBlackboardComponent()->SetValue<UBlackboardKeyType_Vector>(myController->PatrolLocationKey, Loc);
			return EBTNodeResult::Succeeded;
		}
	}
	return EBTNodeResult::Failed;

}
