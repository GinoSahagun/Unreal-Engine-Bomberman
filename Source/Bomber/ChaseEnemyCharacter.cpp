// Fill out your copyright notice in the Description page of Project Settings.

#include "Bomber.h"
#include "ChaseEnemyCharacter.h"
#include "EnemyAIController.h"


/* AI Include */
#include "Perception/PawnSensingComponent.h"

// Sets default values
AChaseEnemyCharacter::AChaseEnemyCharacter()
	: Super()
{
	/* Note: We assign the Controller class in the Blueprint extension of this class
	Because the zombie AIController is a blueprint in content and it's better to avoid content references in code.  */
	/*AIControllerClass = ASZombieAIController::StaticClass();*/

	/* Our sensing component to detect players by visibility and noise checks. */
	PawnSensingComp = CreateDefaultSubobject<UPawnSensingComponent>(TEXT("PawnSensingComp"));
	PawnSensingComp->SetPeripheralVisionAngle(60.0f);
	PawnSensingComp->SightRadius = 2000;
	PawnSensingComp->HearingThreshold = 600;
	PawnSensingComp->LOSHearingThreshold = 1200;

	SenseTimeOut = 2.5f;

	/* Note: Visual Setup is done in the AI/ZombieCharacter Blueprint file */
}


void AChaseEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();
	/* This is the earliest moment we can bind our delegates to the component */
	if (PawnSensingComp)
	{
		PawnSensingComp->OnSeePawn.AddDynamic(this, &AChaseEnemyCharacter::OnSeePlayer);
		PawnSensingComp->OnHearNoise.AddDynamic(this, &AChaseEnemyCharacter::OnHearNoise);
	}
}

void AChaseEnemyCharacter::Tick(float DeltaSeconds)

{
	Super::Tick(DeltaSeconds);
}

void AChaseEnemyCharacter::OnSeePlayer(APawn* Pawn)
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


void AChaseEnemyCharacter::OnHearNoise(APawn* PawnInstigator, const FVector& Location, float Volume)
{

	bSensedTarget = true;
	LastHeardTime = GetWorld()->GetTimeSeconds();

	AEnemyAIController* AIController = Cast<AEnemyAIController>(GetController());
	if (AIController)
	{
		AIController->SetTargetEnemy(PawnInstigator);
	}
}











