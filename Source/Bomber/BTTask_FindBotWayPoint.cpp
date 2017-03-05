// Fill out your copyright notice in the Description page of Project Settings.

#include "Bomber.h"
#include "BTTask_FindBotWayPoint.h"
/* AI Specific includes */
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyAllTypes.h"

/* AI Enemy Character Include*/
#include "EnemyCharacter.h"
#include "EnemyAIController.h"
#include "BomberCharacter.h"
EBTNodeResult::Type UBTTask_FindBotWayPoint::ExecuteTask(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory)
{
	AEnemyAIController* myController = Cast<AEnemyAIController>(OwnerComp.GetAIOwner());
	if (myController == nullptr)
	{
		return EBTNodeResult::Failed;
		GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Green, "Cant Get Controller");
	}
	ASBotWayPoint* currentPoint = myController->GetWaypoint();
	AActor* newWayPoint = nullptr;

	/* Iterate all the bot waypoints in the current level and find a new random waypoint to set as destination */
	TArray<AActor*> allWayPoints;
	UGameplayStatics::GetAllActorsOfClass(myController, ASBotWayPoint::StaticClass(), allWayPoints);
	
	if (allWayPoints.Num() == 0)
	{
		return EBTNodeResult::Failed;
		GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Green, "Cant Find WayPoints");
	}
	/* Find a new waypoint randomly by index (this can include the current waypoint) */
	/* For more complex or human AI you could add some weights based on distance and other environmental conditions here */
	
	newWayPoint = allWayPoints[FMath::RandRange(0, allWayPoints.Num() - 1)];
	/* Assign the new waypoint to the Blackboard */
	if (newWayPoint)
	{
		/* The selected key should be "CurrentWaypoint" in the BehaviorTree setup */
		OwnerComp.GetBlackboardComponent()->SetValue<UBlackboardKeyType_Object>(myController->CurrentWaypointKey, newWayPoint);
		return EBTNodeResult::Succeeded;
	}

	return EBTNodeResult::Failed;
}
