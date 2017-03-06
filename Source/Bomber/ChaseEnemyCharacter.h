// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EnemyCharacter.h"
#include "ChaseEnemyCharacter.generated.h"

/**
 * 
 */
UCLASS()
class BOMBER_API AChaseEnemyCharacter : public AEnemyCharacter
{
	GENERATED_BODY()



	UPROPERTY(VisibleAnywhere, Category = "AI")
	class UPawnSensingComponent* PawnSensingComp;

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaSeconds) override;

protected:

	/* Triggered by pawn sensing component when a pawn is spotted */
	/* When using functions as delegates they need to be marked with UFUNCTION(). We assign this function to FSeePawnDelegate */
	UFUNCTION()
		void OnSeePlayer(APawn* Pawn);

	UFUNCTION()
		void OnHearNoise(APawn* PawnInstigator, const FVector& Location, float Volume);

public:

	AChaseEnemyCharacter();

};
