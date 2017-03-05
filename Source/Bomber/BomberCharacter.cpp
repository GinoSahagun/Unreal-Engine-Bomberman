// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#include "Bomber.h"
#include "BomberCharacter.h"
#include "Runtime/CoreUObject/Public/UObject/ConstructorHelpers.h"
#include "Runtime/Engine/Classes/Components/DecalComponent.h"
#include "Kismet/HeadMountedDisplayFunctionLibrary.h"

ABomberCharacter::ABomberCharacter()
{
	// Set size for player capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);


	// Don't rotate character to camera direction
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Rotate character to moving direction
	GetCharacterMovement()->RotationRate = FRotator(0.f, 640.f, 0.f);
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;

	// Create a camera boom...
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->bAbsoluteRotation = true; // Don't want arm to rotate when character does
	CameraBoom->TargetArmLength = 1000.f;
	CameraBoom->RelativeRotation = FRotator(-60.f, 0.f, 0.f);
	CameraBoom->bDoCollisionTest = false; // Don't want to pull camera in when it collides with level

										  // Create a camera...
	TopDownCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("TopDownCamera"));
	TopDownCameraComponent->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	TopDownCameraComponent->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	
	// Create a decal in the world to show the cursor's location
	CursorToWorld = CreateDefaultSubobject<UDecalComponent>("CursorToWorld");
	CursorToWorld->SetupAttachment(RootComponent);
	
	static ConstructorHelpers::FObjectFinder<UMaterial> DecalMaterialAsset(TEXT("Material'/Game/TopDownCPP/Blueprints/M_Cursor_Decal.M_Cursor_Decal'"));
	
	//Init. text render comp
	//CharText = CreateDefaultSubobject<UTextRenderComponent>(FName("CharText"));

	//Set a relative location
	//CharText->SetRelativeLocation(FVector(0, 0, 100));

	//Attach it to root comp
	//CharText->SetupAttachment(GetRootComponent());
	//Create a string that will display the health and bomb count values
	//FString NewText = FString("Health: ") + FString::SanitizeFloat(Health) + FString(" Bomb Count: ") + FString::FromInt(BombCount);

	//Set the created string to the text render comp
	//CharText->SetText(FText::FromString(NewText));
	if (DecalMaterialAsset.Succeeded())
	{
		CursorToWorld->SetDecalMaterial(DecalMaterialAsset.Object);
	}
	CursorToWorld->DecalSize = FVector(16.0f, 32.0f, 32.0f);
	CursorToWorld->SetRelativeRotation(FRotator(90.0f, 0.0f, 0.0f).Quaternion());

	// Activate ticking in order to update the cursor every frame.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;

	InitHealth();
	InitBombCount();

}

void ABomberCharacter::Tick(float DeltaSeconds)
{
	if (CursorToWorld != nullptr)
	{
		if (UHeadMountedDisplayFunctionLibrary::IsHeadMountedDisplayEnabled())
		{
			if (UWorld* World = GetWorld())
			{
				FHitResult HitResult;
				FCollisionQueryParams Params;
				FVector StartLocation = TopDownCameraComponent->GetComponentLocation();
				FVector EndLocation = TopDownCameraComponent->GetComponentRotation().Vector() * 2000.0f;
				Params.AddIgnoredActor(this);
				World->LineTraceSingleByChannel(HitResult, StartLocation, EndLocation, ECC_Visibility, Params);
				FQuat SurfaceRotation = HitResult.ImpactNormal.ToOrientationRotator().Quaternion();
				CursorToWorld->SetWorldLocationAndRotation(HitResult.Location, SurfaceRotation);
			}
		}
		else if (APlayerController* PC = Cast<APlayerController>(GetController()))
		{
			FHitResult TraceHitResult;
			PC->GetHitResultUnderCursor(ECC_Visibility, true, TraceHitResult);
			FVector CursorFV = TraceHitResult.ImpactNormal;
			FRotator CursorR = CursorFV.Rotation();
			CursorToWorld->SetWorldLocation(TraceHitResult.Location);
			CursorToWorld->SetWorldRotation(CursorR);
		}
	}
}


void ABomberCharacter::InitHealth()
{
	Health = MaxHealth;
	//UpdateCharText();
}

void ABomberCharacter::InitBombCount()
{
	BombCount = MaxBombCount;
	//UpdateCharText();
}

bool ABomberCharacter::IsAlive()
{
	return true;
}



float ABomberCharacter::TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	Super::TakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser);

	//Decrease the character's hp 

	Health -= Damage;
	if (Health <= 0) InitHealth();

	//Call the update text on the local client
	//OnRep_Health will be called in every other client so the character's text
	//will contain a text with the right values
	//UpdateCharText();

	return Health;
}



void ABomberCharacter::AttempToSpawnBomb()
{
	if (HasBombs())
	{
		
		SpawnBomb();

		//todo: this code will be removed in the next part
		
	}
	
}

void ABomberCharacter::SpawnBomb()
{
	//Decrease the bomb count and update the text in the local client
	//OnRep_BombCount will be called in every other client
	//BombCount--;
	//UpdateCharText();

	//todo: spawn the actual bomb in the next part of the tutorial
	FActorSpawnParameters SpawnParameters;
	SpawnParameters.Instigator = this;
	SpawnParameters.Owner = GetController();

	//Spawn the bomb
	GetWorld()->SpawnActor<ABomb>(BombActorBP,GetActorLocation() - GetActorForwardVector(), GetActorRotation(), SpawnParameters);
	//GetWorld()->SpawnActor<ABomb>(BombActorBP, GetActorLocation() + GetActorForwardVector() * 200, GetActorRotation(), SpawnParameters);
	//BombCount++;
	
}



