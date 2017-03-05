// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Info.h"
#include "ASMutator.generated.h"

/**
 * 
 */
UCLASS(Blueprintable, Abstract, Meta = (ChildCanTick))
class BOMBER_API AASMutator : public AInfo
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintNativeEvent, BlueprintAuthorityOnly)
		void InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage);

	virtual void InitGame_Implementation(const FString& MapName, const FString& Options, FString& ErrorMessage);

	/* Next mutator in the chain */
	AASMutator* NextMutator;

	/** From UT: entry point for mutators modifying, replacing, or destroying Actors
	* return false to destroy Other
	* note that certain critical Actors such as PlayerControllers can't be destroyed, but we'll still call this code path to allow mutators
	* to change properties on them
	* MAKE SURE TO CALL SUPER TO PROCESS ADDITIONAL MUTATORS
	*/
	UFUNCTION(BlueprintNativeEvent, BlueprintAuthorityOnly)
		bool CheckRelevance(AActor* Other);

	/* Note: Functions flagged with BlueprintNativeEvent like above require _Implementation for a C++ implementation */
	virtual bool CheckRelevance_Implementation(AActor* Other);

};

