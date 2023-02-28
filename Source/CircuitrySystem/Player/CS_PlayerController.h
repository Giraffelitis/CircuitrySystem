// Copyright 2023 by Pace Abbott. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "EnhancedInputComponent.h"
#include "CS_PlayerController.generated.h"

class UCS_InputConfig;
class ACS_PlayerCharacter;

/**
 * 
 */

UCLASS()
class CIRCUITRYSYSTEM_API ACS_PlayerController : public APlayerController
{
	GENERATED_BODY()

public:

	ACS_PlayerController();
	
	/** The input config that maps Input Actions to Input Tags*/
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	UCS_InputConfig* InputConfig;

	/** Handles moving forward/backward */
	void Input_Move(const FInputActionValue& InputActionValue);

	/** Handles mouse and stick look */
	void Input_Look(const FInputActionValue& InputActionValue);

	/** Handles Jumping */
	void Input_Jump(const FInputActionValue& InputActionValue);

	/** Handles Pickup */
	void Input_Pickup(const FInputActionValue& InputActionValue);

	/** Handles Primary Support Action */
	void Input_Primary_Support_Action(const FInputActionValue& InputActionValue);

	/** Handles Secondary Support Action */
	void Input_Secondary_Support_Action(const FInputActionValue& InputActionValue);

	/** Handles Input Modifier Pressed */
	void Input_Modifier_Pressed(const FInputActionValue& InputActionValue);

	/** Handles Input Modifier Released */
	void Input_Modifier_Released(const FInputActionValue& InputActionValue);


	/**
	 * Called via input to turn at a given rate.
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void TurnAtRate(float Rate);

	/**
	 * Called via input to turn look up/down at a given rate.
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void LookUpAtRate(float Rate);
	
	//virtual void SetupInputComponent() override;
	void SetupInput();

	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	float TurnRateGamepad;

	UPROPERTY()
	ACS_PlayerCharacter* CS_Character;

};
