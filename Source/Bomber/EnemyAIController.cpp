// Fill out your copyright notice in the Description page of Project Settings.

#include "Bomber.h"
#include "EnemyAIController.h"
/* AI Specific includes */
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyAllTypes.h"

/* AI Enemy Character Include*/
#include "EnemyCharacter.h"

AEnemyAIController::AEnemyAIController()
{
	blackBoardComp = CreateDefaultSubobject<UBlackboardComponent>(TEXT("blackBoardComp"));

	behaviorComp = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("behaviorComp"));

}

void AEnemyAIController::Possess(APawn * InPawn)
{

	Super::Possess(InPawn);

	AEnemyCharacter* AIChar = Cast<AEnemyCharacter>(InPawn);
	
	if (AIChar && AIChar->BotBehavior)
	{
		blackBoardComp->InitializeBlackboard(*AIChar->BotBehavior->BlackboardAsset);

		ENEMY_KEY_ID = blackBoardComp->GetKeyID("Target");

		behaviorComp->StartTree(*AIChar->BotBehavior);
	}

}
