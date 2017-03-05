// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

/**
 * 
 */
UENUM()
enum class EBotBehaviorType : uint8
{
	/* Does not move, remains in place until a player is spotted */
	Passive,

	/* Patrols a region until a player is spotted */
	Patrolling,
};
class BOMBER_API STypes
{
public:
	STypes();
	~STypes();
};
