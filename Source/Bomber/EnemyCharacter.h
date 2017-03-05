// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Character.h"
#include "STypes.h"
#include "EnemyCharacter.generated.h"

UCLASS(ABSTRACT)
class BOMBER_API AEnemyCharacter : public ACharacter
{
	GENERATED_BODY()



public:

	AEnemyCharacter();
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaSeconds) override;

	/* The bot behavior we want this bot to execute, (passive/patrol) by specifying EditAnywhere we can edit this value per-instance when placed on the map. */
	UPROPERTY(EditAnywhere, Category = "AI")
	EBotBehaviorType BotType;

	/* The thinking part of the brain, steers our zombie and makes decisions based on the data we feed it from the Blackboard */
	/* Assigned at the Character level (instead of Controller) so we may use different zombie behaviors while re-using one controller. */
	UPROPERTY(EditDefaultsOnly, Category = "AI")
	class UBehaviorTree* BehaviorTree;

	/* Change default bot type during gameplay */
	void SetBotType(EBotBehaviorType NewType);
};
