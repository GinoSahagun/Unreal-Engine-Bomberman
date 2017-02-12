// Fill out your copyright notice in the Description page of Project Settings.

#include "Bomber.h"
#include "BomberCharacter.h"
#include "BTService_CheckForPlayer.h"

/* AI Specific includes */
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyAllTypes.h"


/* AI Enemy Character Include*/
#include "EnemyCharacter.h"
#include "EnemyAIController.h"
UBTService_CheckForPlayer::UBTService_CheckForPlayer()
{
	bCreateNodeInstance = true;
}

void UBTService_CheckForPlayer::TickNode(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory, float DeltaSeconds)
{
	AEnemyAIController* controller = Cast<AEnemyAIController>(OwnerComp.GetAIOwner());

	if (controller)
	{
		ABomberCharacter* Enemy = Cast<ABomberCharacter>(GetWorld()->GetFirstPlayerController()->GetPawn());

		if (Enemy)
		{
			OwnerComp.GetBlackboardComponent()->SetValue<UBlackboardKeyType_Object>(controller->ENEMY_KEY_ID, Enemy);
			//GEngine->AddOnScreenDebugMessage(-1, 2.f,FColor::Green, "Enemy Here");


		}
	
	}
}
