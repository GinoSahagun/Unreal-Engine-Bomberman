// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AIController.h"
#include "EnemyAIController.generated.h"

/**
 * 
 */
UCLASS()
class BOMBER_API AEnemyAIController : public AAIController
{
	GENERATED_BODY()

	UPROPERTY(transient)
	class UBlackboardComponent* blackBoardComp;
	UPROPERTY(transient)
	class UBehaviorTreeComponent* behaviorComp;
public:
	AEnemyAIController();

	virtual void Possess(APawn* InPawn) override;

	uint8 ENEMY_KEY_ID;


private:

	
};
