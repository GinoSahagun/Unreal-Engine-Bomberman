// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BehaviorTree/BTService.h"
#include "BTService_CheckForPlayer.generated.h"


/**
 * 
 */
UCLASS()
class BOMBER_API UBTService_CheckForPlayer : public UBTService
{
	GENERATED_BODY()
	
public:
	UBTService_CheckForPlayer();
	/** update next tick interval
	* this function should be considered as const (don't modify state of object) if node is not instanced! */
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
	
	
};
