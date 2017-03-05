// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine/TargetPoint.h"
#include "SBotWayPoint.generated.h"
/**
* Waypoint helper for bots to generate waypoints during patrols. Object is placed in level to specify a potential patrol target location.
*/
UCLASS()
class BOMBER_API ASBotWayPoint : public ATargetPoint
{
	GENERATED_BODY()
	
};
