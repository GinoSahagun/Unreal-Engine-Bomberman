// Fill out your copyright notice in the Description page of Project Settings.

#include "Bomber.h"
#include "BTTask_MoveToPlayer.h"

/* AI Specific includes */
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyAllTypes.h"

/* AI Enemy Character Include*/
#include "EnemyCharacter.h"
#include "EnemyAIController.h"
#include "BomberCharacter.h"

EBTNodeResult::Type UBTTask_MoveToPlayer::ExecuteTask(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory)
{
	AEnemyAIController* AIController = Cast<AEnemyAIController>(OwnerComp.GetAIOwner());
	
	ABomberCharacter* Enemy = Cast<ABomberCharacter>(OwnerComp.GetBlackboardComponent()->GetValue<UBlackboardKeyType_Object>(AIController->ENEMY_KEY_ID));

	if (Enemy)
	{
		AIController->MoveToActor(Enemy, 1.f, true, true, true, 0, true);

		return EBTNodeResult::Succeeded;
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Green, "Not Working");
		return EBTNodeResult::Failed;
	}
	return EBTNodeResult::Failed;
}
