// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AIController.h"
#include "SBotWayPoint.h"
#include "BomberCharacter.h"
#include "STypes.h"
#include "EnemyAIController.generated.h"

/**
*
*/
UCLASS()
class BOMBER_API AEnemyAIController : public AAIController
{
	GENERATED_BODY()

	AEnemyAIController();

	/* Called whenever the controller possesses a character bot */
	virtual void Possess(APawn* InPawn) override;

	virtual void UnPossess() override;

	UBehaviorTreeComponent* BehaviorComp;

	UBlackboardComponent* BlackboardComp;

	UPROPERTY(EditDefaultsOnly, Category = "AI")
		FName TargetEnemyKeyName;

	UPROPERTY(EditDefaultsOnly, Category = "AI")
		FName PatrolLocationKeyName;

	UPROPERTY(EditDefaultsOnly, Category = "AI")
		FName CurrentWaypointKeyName;

	UPROPERTY(EditDefaultsOnly, Category = "AI")
		FName BotTypeKeyName;




public:
	ASBotWayPoint* GetWaypoint();

	ABomberCharacter* GetTargetEnemy();

	void SetWaypoint(ASBotWayPoint* NewWaypoint);

	void SetTargetEnemy(APawn* NewTarget);

	void SetBlackboardBotType(EBotBehaviorType NewType);

	
		uint8 TargetEnemyKey;


		uint8 PatrolLocationKey;


		uint8 CurrentWaypointKey;


		uint8 BotTypeKey;

	/** Returns BehaviorComp subobject **/
	FORCEINLINE UBehaviorTreeComponent* GetBehaviorComp() const { return BehaviorComp; }

	FORCEINLINE UBlackboardComponent* GetBlackboardComp() const { return BlackboardComp; }
};