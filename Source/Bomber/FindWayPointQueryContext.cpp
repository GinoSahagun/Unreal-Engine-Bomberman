// Fill out your copyright notice in the Description page of Project Settings.

#include "Bomber.h"
#include "FindWayPointQueryContext.h"
#include "SmartAI.h"
#include "EnemyAIController.h"
#include "SBotWayPoint.h"
/*AI INcludes*/
#include "EnvironmentQuery/EnvQueryTypes.h"
#include "EnvironmentQuery/Items/EnvQueryItemType_Actor.h"


void UFindWayPointQueryContext::ProvideContext(FEnvQueryInstance & QueryInstance, FEnvQueryContextData & ContextData) const
{
	Super::ProvideContext(QueryInstance, ContextData);

	//Get the Owner of this Query and cast it to an actor
	//Then, get the actor's controller and cast to it our AIController
	//This code works for our case but avoid that many casts and one-liners in cpp.
	AEnemyAIController* myController = Cast<AEnemyAIController>((Cast<AActor>((QueryInstance.Owner).Get())));
	

	if (myController && myController->GetSeeingPawn())
	{
		//Set the context SeeingPawn to the provided context data
		UEnvQueryItemType_Actor::SetContextHelper(ContextData, myController->GetSeeingPawn());
	}


}
