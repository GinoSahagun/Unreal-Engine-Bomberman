// Fill out your copyright notice in the Description page of Project Settings.

#include "Bomber.h"
#include "EnemyCharacter.h"
#include "EnemyAIController.h"
#include "SBotWaypoint.h"

AEnemyCharacter::AEnemyCharacter()
{
	/* Note: We assign the Controller class in the Blueprint extension of this class
	Because the zombie AIController is a blueprint in content and it's better to avoid content references in code.  */
	/*AIControllerClass = ASZombieAIController::StaticClass();*/
	

	/* Note: Visual Setup is done in the AI/ZombieCharacter Blueprint file */
	BotType = EBotBehaviorType::Patrolling;
}

void AEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();

}


void AEnemyCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

}


void AEnemyCharacter::SetBotType(EBotBehaviorType NewType)
{
	BotType = NewType;

	AEnemyAIController* AIController = Cast<AEnemyAIController>(GetController());
	if (AIController)
	{
		AIController->SetBlackboardBotType(NewType);
	}

}







