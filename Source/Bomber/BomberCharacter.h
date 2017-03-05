// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.
#pragma once
#include "Net/UnrealNetwork.h"
#include "Engine.h"
#include "GameFramework/Character.h"
#include "Bomb.h"
#include "BomberCharacter.generated.h"

UCLASS(Blueprintable)
class ABomberCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	//Constructor Bomb Character
	ABomberCharacter();
	FORCEINLINE class UCameraComponent* GetTopDownCameraComponent() const { return TopDownCameraComponent; }
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns CursorToWorld subobject **/
	FORCEINLINE class UDecalComponent* GetCursorToWorld() { return CursorToWorld; }

	//Bomb Blue Prints
	UPROPERTY(EditAnywhere)
	TSubclassOf<ABomb> BombActorBP;

	

	// Called every frame.
	virtual void Tick(float DeltaSeconds) override;
	
	/** Returns TopDownCameraComponent subobject **/
	/** Text render component - used instead of UMG, to keep the tutorial short */
	//UPROPERTY(VisibleAnywhere)
	//UTextRenderComponent* CharText;
	//virtual void SetupInputComponent() override;
	//player Controls for ASWD
	//void SetupPlayerInputComponent(class UInputComponent* InputComponent);
	
	

	/** The max number of bombs that a character can have */
	UPROPERTY(EditAnywhere, Category = Stats)
		int32 MaxBombCount = 2;
	
	/** Initializes health */
	void InitHealth();

	/** Initializes bomb count */
	void InitBombCount();

	bool IsAlive();

	/** Updates the character's text to match with the updated stats */
	//void UpdateCharText();
	/**
	* TakeDamage Server version. Call this instead of TakeDamage when you're a client
	* You don't have to generate an implementation. It will automatically call the ServerTakeDamage_Implementation function
	*/
	//Bomb related functions

	/** Will try to spawn a bomb */
	void AttempToSpawnBomb();

	/** Returns true if we can throw a bomb */
	bool HasBombs() { return BombCount > 0; }

	/**
	* Spawns a bomb. Call this function when you're authorized to.
	* In case you're not authorized, use the ServerSpawnBomb function.
	*/
	void SpawnBomb();

	/** Applies damage to the character */
	virtual float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;
	/** The number of bombs that the character used */
	UPROPERTY(EditAnywhere, Transient, Category = Stats)
	int32 BombCount;
private:
	/** Top down camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class UCameraComponent* TopDownCameraComponent;

	/** Camera boom positioning the camera above the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class USpringArmComponent* CameraBoom;

	/** A decal that projects to the cursor location. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class UDecalComponent* CursorToWorld;
	/** The health of the character */
	UPROPERTY(EditAnywhere, Category = Stats)
		int Health;

	/** The max health of the character */
	UPROPERTY(EditAnywhere, Category = Stats)
		int MaxHealth = 100;

	
	

};




