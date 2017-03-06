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

	BehaviorComp = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("behaviorComp"));
	BlackboardComp = CreateDefaultSubobject<UBlackboardComponent>(TEXT("blackBoardComp"));

	/* Match with the AI/ZombieBlackboard */
	PatrolLocationKeyName = "PatrolLocation";
	CurrentWaypointKeyName = "CurrentWayPoint";
	BotTypeKeyName = "BotType";
	TargetEnemyKeyName = "Target";
	TargetLocationKeyName = "TargetLocation";
	/* Initializes PlayerState so we can assign a team index to AI */
	bWantsPlayerState = true;
}

void  AEnemyAIController::Possess(APawn* InPawn)
{
	Super::Possess(InPawn);

	AEnemyCharacter* ZombieBot = Cast<AEnemyCharacter>(InPawn);
	if (ZombieBot)
	{
		if (ZombieBot->BehaviorTree->BlackboardAsset)
		{
			BlackboardComp->InitializeBlackboard(*ZombieBot->BehaviorTree->BlackboardAsset);
			//set key ids
			TargetEnemyKey = BlackboardComp->GetKeyID(TargetEnemyKeyName);
			BotTypeKey = BlackboardComp->GetKeyID(BotTypeKeyName);
			CurrentWaypointKey = BlackboardComp->GetKeyID(CurrentWaypointKeyName);
			PatrolLocationKey = BlackboardComp->GetKeyID(PatrolLocationKeyName);
			TargetLocationKey = BlackboardComp->GetKeyID(TargetLocationKeyName);
			/* Make sure the Blackboard has the type of bot we possessed */
			SetBlackboardBotType(ZombieBot->BotType);
		}

		BehaviorComp->StartTree(*ZombieBot->BehaviorTree);
	}
}


void AEnemyAIController::UnPossess()
{
	Super::UnPossess();

	/* Stop any behavior running as we no longer have a pawn to control */
	BehaviorComp->StopTree();
}


void AEnemyAIController::SetWaypoint(ASBotWayPoint* NewWaypoint)
{
	if (BlackboardComp)
	{
		BlackboardComp->SetValueAsObject(CurrentWaypointKeyName, NewWaypoint);
	}
}


void AEnemyAIController::SetTargetEnemy(APawn* NewTarget)
{

	if (BlackboardComp)
	{
		BlackboardComp->SetValue<UBlackboardKeyType_Object>(TargetEnemyKey, NewTarget);
		BlackboardComp->SetValue<UBlackboardKeyType_Vector>(TargetLocationKey, NewTarget->GetActorLocation());
		//BlackboardComp->SetValueAsObject(TargetEnemyKey, NewTarget);
	}
}


ASBotWayPoint* AEnemyAIController::GetWaypoint()
{
	if (BlackboardComp)
	{
		return Cast<ASBotWayPoint>(BlackboardComp->GetValueAsObject(CurrentWaypointKeyName));
	}

	return nullptr;
}


ABomberCharacter* AEnemyAIController::GetTargetEnemy()
{
	if (BlackboardComp)
	{
		return Cast<ABomberCharacter>(BlackboardComp->GetValueAsObject(TargetEnemyKeyName));
	}

	return nullptr;
}


void AEnemyAIController::SetBlackboardBotType(EBotBehaviorType NewType)
{
	if (BlackboardComp)
	{
		BlackboardComp->SetValueAsEnum(BotTypeKeyName, (uint8) NewType);
	}
}

AActor* AEnemyAIController::GetSeeingPawn()
{
	//Return the seeing pawn
	
	UObject* object = BlackboardComp->GetValue<UBlackboardKeyType_Object>(TargetEnemyKey);

	return object ? Cast<AActor>(object) : nullptr;
}