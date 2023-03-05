// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "CS_PlayerCharacter.generated.h"

class ACS_BuildHelperMesh;
class UPhysicsHandleComponent;
class UCameraComponent;
struct FInputActionValue;
class UStaticMeshComponent;
class UCS_InputConfig;

UCLASS()
class CIRCUITRYSYSTEM_API ACS_PlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	
	ACS_PlayerCharacter();

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* f_PlayerInputComponent) override;

	virtual void Tick(float DeltaTime) override;
	
	virtual void BeginPlay() override;

	void StartJump();
	virtual void Jump() override;
	void EndJump();
	virtual void StopJumping() override;
	
	void StartCrouch();
	virtual void Crouch(bool f_bClientSimulation) override;
	void EndCrouch();
	virtual void UnCrouch(bool f_bClientSimulation) override;
	
	void ApplyAltModifier();
	void RemoveAltModifier();	
	bool GetAltModifier() const { return bInBuildMode; }
	void SetAltModifier(bool f_Enabled);
	
	void ApplyShiftModifier();
	void RemoveShiftModifier();	
	bool GetShiftModifier() const { return bInBuildMode; }
	void SetShiftModifier(bool f_Enabled);
	
	void InputMouseWheelUp(const FInputActionValue& f_InputActionValue);
	void InputMouseWheelDown(const FInputActionValue& f_InputActionValue);


	virtual void FellOutOfWorld(const UDamageType& f_DmgType) override;
	void OnDeath(bool f_IsFellOut);

	void RotateObjectPos(const FInputActionValue& f_InputActionValue);
	
	void RotateObjectNeg(const FInputActionValue& f_InputActionValue);

	UFUNCTION()
	void PickupItem();

	UPROPERTY()
	FRotator CarriedObjectRotation;
	
	UPROPERTY(EditAnywhere)
	float CarryOffset;
	
	UPROPERTY()
	bool AltModifier;
	
	bool ShiftModifier;

	/** The input config that maps Input Actions to Input Tags*/
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	UCS_InputConfig* InputConfig;
	
protected:
	
	UPROPERTY(EditAnywhere, Category = "Item Pickup")
	float InteractDistance;

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

	/**************************************/
	/* Build Mode for all Characters */
	/**************************************/

	public:
	
	UFUNCTION(BlueprintCallable, Category = "Build")
	void ToggleBuildMode();
	
	FHitResult BuildHelperLineTrace(float f_MaxBuildDistance);

	UFUNCTION(BlueprintCallable, Category = "Build")
	bool GetBuildMode() const { return bInBuildMode; }
	
	UFUNCTION(BlueprintCallable, Category = "Build")
	void SetBuildMode(bool f_Enabled);
	
	UFUNCTION(BlueprintCallable, Category = "Build")
	void SpawnBuildComponent();

	UFUNCTION()
	void DestroyBuildComponent();
	
protected:
	
	UPROPERTY(EditDefaultsOnly, Category = "Build")
	TSubclassOf<ACS_BuildHelperMesh> BuildClass;
	
	UPROPERTY(EditAnywhere, Category = "Build")
	ACS_BuildHelperMesh* BuildHelper;

	UPROPERTY(BlueprintReadOnly, Category = "Build")
	float MaxBuildDistance;
	
	UPROPERTY(BlueprintReadOnly, Category = "Build")
	bool bInBuildMode;
};


