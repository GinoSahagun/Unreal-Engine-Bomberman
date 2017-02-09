// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#include "Bomber.h"
#include "BomberGameMode.h"
#include "BomberPlayerController.h"
#include "BomberCharacter.h"

ABomberGameMode::ABomberGameMode()
{
	// use our custom PlayerController class
	PlayerControllerClass = ABomberPlayerController::StaticClass();
	
	// set default pawn class to our Blueprinted character
	//static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/TopDownCPP/Blueprints/TopDownCharacter"));
	/*static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Classes_Game/Bomber/BomberCharacter.cpp"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}*/

	static ConstructorHelpers::FClassFinder<APawn> PawnClassAsset(TEXT("/Game/TopDownCPP/Blueprints/MyBomberCharacter"));
	if (PawnClassAsset.Succeeded())
	{
		DefaultPawnClass = PawnClassAsset.Class;
	}
	
	
}