// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#include "Bomber.h"
#include "BomberPlayerController.h"
#include "AI/Navigation/NavigationSystem.h"
#include "Runtime/Engine/Classes/Components/DecalComponent.h"
#include "Kismet/HeadMountedDisplayFunctionLibrary.h"
#include "BomberCharacter.h"
#include "Bomb.h"


ABomberPlayerController::ABomberPlayerController()
{
	
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Crosshairs;
	
}

void ABomberPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);

	// keep updating the destination every tick while desired
	if (bMoveToMouseCursor)
	{
		MoveToMouseCursor();
	}
}

void ABomberPlayerController::SetupInputComponent()
{
	// set up gameplay key bindings
	Super::SetupInputComponent();

	InputComponent->BindAction("SetDestination", IE_Pressed, this, &ABomberPlayerController::OnSetDestinationPressed);
	InputComponent->BindAction("SetDestination", IE_Released, this, &ABomberPlayerController::OnSetDestinationReleased);
	InputComponent->BindAxis("MoveForward", this, &ABomberPlayerController::MoveForward);
	InputComponent->BindAxis("MoveRight", this, &ABomberPlayerController::MoveRight);
	//InputComponent->BindAction("spawnBomb",IE_Pressed, this, &ABomberPlayerController::spawnBomb);
	
	// support touch devices 
	InputComponent->BindTouch(EInputEvent::IE_Pressed, this, &ABomberPlayerController::MoveToTouchLocation);
	InputComponent->BindTouch(EInputEvent::IE_Repeat, this, &ABomberPlayerController::MoveToTouchLocation);

	InputComponent->BindAction("ResetVR", IE_Pressed, this, &ABomberPlayerController::OnResetVR);
}


void ABomberPlayerController::MoveForward(float Value)
{
	
	ACharacter* sup = Cast<ABomberCharacter>(GetCharacter());
	
	//AYourCharacter* Pawn = Cast(GetCharacter());

	if ((sup->Controller != NULL) && (Value != 0.0f))
	{
		FRotator Rotation = sup->Controller->GetControlRotation();
		const FVector Direction = FRotationMatrix(Rotation).GetScaledAxis(EAxis::X);
		sup->AddMovementInput(Direction, Value);
		
	}
}

void ABomberPlayerController::MoveRight(float Value)
{
	
	ACharacter* sup = Cast<ABomberCharacter>(GetCharacter());
	
	//AYourCharacter* Pawn = Cast(GetCharacter());

	if ((sup->Controller != NULL) && (Value != 0.0f))
	{
		FRotator Rotation = sup->Controller->GetControlRotation();
		const FVector Direction = FRotationMatrix(Rotation).GetScaledAxis(EAxis::Y);
		sup->AddMovementInput(Direction, Value);
	}
}

void ABomberPlayerController::spawnBomb()
{
	//got to get player character class to spawn bomb
	ABomberCharacter* MyPawn = Cast<ABomberCharacter>(GetPawn());

	MyPawn->AttempToSpawnBomb();
	
}



void ABomberPlayerController::OnResetVR()
{
	UHeadMountedDisplayFunctionLibrary::ResetOrientationAndPosition();
}

void ABomberPlayerController::MoveToMouseCursor()
{
	if (UHeadMountedDisplayFunctionLibrary::IsHeadMountedDisplayEnabled())
	{
		if (ABomberCharacter* MyPawn = Cast<ABomberCharacter>(GetPawn()))
		{
			if (MyPawn->GetCursorToWorld())
			{
				UNavigationSystem::SimpleMoveToLocation(this, MyPawn->GetCursorToWorld()->GetComponentLocation());
			}
		}
	}
	else
	{
		// Trace to see what is under the mouse cursor
		FHitResult Hit;
		GetHitResultUnderCursor(ECC_Visibility, false, Hit);

		if (Hit.bBlockingHit)
		{
			// We hit something, move there
			SetNewMoveDestination(Hit.ImpactPoint);
		}
	}
}

void ABomberPlayerController::MoveToTouchLocation(const ETouchIndex::Type FingerIndex, const FVector Location)
{
	FVector2D ScreenSpaceLocation(Location);

	// Trace to see what is under the touch location
	FHitResult HitResult;
	GetHitResultAtScreenPosition(ScreenSpaceLocation, CurrentClickTraceChannel, true, HitResult);
	if (HitResult.bBlockingHit)
	{
		// We hit something, move there
		SetNewMoveDestination(HitResult.ImpactPoint);
	}
}

void ABomberPlayerController::SetNewMoveDestination(const FVector DestLocation)
{
	APawn* const MyPawn = GetPawn();
	if (MyPawn)
	{
		UNavigationSystem* const NavSys = GetWorld()->GetNavigationSystem();
		float const Distance = FVector::Dist(DestLocation, MyPawn->GetActorLocation());

		// We need to issue move command only if far enough in order for walk animation to play correctly
		if (NavSys && (Distance > 120.0f))
		{
			NavSys->SimpleMoveToLocation(this, DestLocation);
		}
	}
}

void ABomberPlayerController::OnSetDestinationPressed()
{
	// set flag to keep updating destination until released
	bMoveToMouseCursor = true;
}

void ABomberPlayerController::OnSetDestinationReleased()
{
	// clear flag to indicate we should stop updating the destination
	bMoveToMouseCursor = false;
}
