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
	void PrimarySupportAction();
	void SecondarySupportAction();

	FRotator CarriedObjectRoation;

	bool InputModifier;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	UPROPERTY(EditAnywhere, Category = "Item Pickup")
	float PickupDistance;

	UPROPERTY(EditAnywhere, Category = "Item Pickup")
	float DefaultDampening;

	UPROPERTY(EditAnywhere, Category = "Item Pickup")
	float RotationDegree;

	UPROPERTY(EditAnywhere, Category = "Item Pickup")
	float ObjectHeldDistance;
	
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
