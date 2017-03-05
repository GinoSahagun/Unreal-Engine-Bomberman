// Fill out your copyright notice in the Description page of Project Settings.

#include "Bomber.h"
#include "SBaseCharacter.h"


// Sets default values
ASBaseCharacter::ASBaseCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ASBaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASBaseCharacter::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

// Called to bind functionality to input
void ASBaseCharacter::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);

}

