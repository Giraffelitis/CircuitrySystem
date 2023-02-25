// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "CS_PlayerCharacter.generated.h"

class UPhysicsHandleComponent;
class UCameraComponent;

UCLASS()
class CIRCUITRYSYSTEM_API ACS_PlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ACS_PlayerCharacter();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void PickupAction();	
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	UPROPERTY(EditAnywhere)
	float PickupDistance;

	UPROPERTY(EditAnywhere)
	float DefaultDampening;

private:
	
	bool bItemPickedUp;
	
	float AdjustedDampening;	

	UPROPERTY()
	UCameraComponent* Camera;

	UPROPERTY(EditAnywhere)
	UPhysicsHandleComponent* PhysicsHandle;

	UPROPERTY(EditAnywhere)
	UArrowComponent* GrabLocation;
};
