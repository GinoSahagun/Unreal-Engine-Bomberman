// Fill out your copyright notice in the Description page of Project Settings.

#include "Bomber.h"
#include "EnemyAIController.h"
#include "SmartAI.h"

/* AI Include */
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyAllTypes.h"
#include "Perception/PawnSensingComponent.h"

// Sets default values
ASmartAI::ASmartAI()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	
	/* Our sensing component to detect players by visibility and noise checks. */
	PawnSensingComp = CreateDefaultSubobject<UPawnSensingComponent>(TEXT("PawnSensingComp"));
	PawnSensingComp->SetPeripheralVisionAngle(60.0f);
	PawnSensingComp->SetPeripheralVisionAngle(60.0f);
	PawnSensingComp->SightRadius = 2000;
	PawnSensingComp->HearingThreshold = 600;
	PawnSensingComp->LOSHearingThreshold = 1200;

	SenseTimeOut = 2.5f;

	/* Note: Visual Setup is done in the AI / Character Blueprint file */
	BotType = EBotBehaviorType::Patrolling;
}

void ASmartAI::SetBotType(EBotBehaviorType NewType)
{
	BotType = NewType;

	AEnemyAIController* AIController = Cast<AEnemyAIController>(GetController());
	if (AIController)
	{
		AIController->SetBlackboardBotType(NewType);
	}

}


// Called when the game starts or when spawned
void ASmartAI::BeginPlay()
{
	Super::BeginPlay();
	/* This is the earliest moment we can bind our delegates to the component */
	if (PawnSensingComp)
	{
		PawnSensingComp->OnSeePawn.AddDynamic(this, &ASmartAI::OnSeePlayer);
		PawnSensingComp->OnHearNoise.AddDynamic(this, &ASmartAI::OnHearNoise);
	}
	
}

// Called every frame
void ASmartAI::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );
	if (bSensedTarget && (GetWorld()->TimeSeconds - LastSeenTime) > SenseTimeOut)
	{
		AEnemyAIController* AIController = Cast<AEnemyAIController>(GetController());
		if (AIController)
		{
			bSensedTarget = false;
			/* Reset */
			AIController->SetTargetEnemy(nullptr);

		}
	}
}


void ASmartAI::OnSeePlayer(APawn * Pawn)
{
	/* Keep track of the time the player was last sensed in order to clear the target */
	LastSeenTime = GetWorld()->GetTimeSeconds();
	bSensedTarget = true;

	AEnemyAIController* AIController = Cast<AEnemyAIController>(GetController());
	ABomberCharacter* SensedPawn = Cast<ABomberCharacter>(Pawn);
	if (AIController && SensedPawn->IsAlive())
	{
		AIController->SetTargetEnemy(SensedPawn);
	}

}

void ASmartAI::OnHearNoise(APawn * PawnInstigator, const FVector & Location, float Volume)
{
	bSensedTarget = true;
	LastHeardTime = GetWorld()->GetTimeSeconds();

	AEnemyAIController* AIController = Cast<AEnemyAIController>(GetController());
	if (AIController)
	{
		AIController->SetTargetEnemy(PawnInstigator);
	}
}



