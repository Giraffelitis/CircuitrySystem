// Copyright 2023 by Pace Abbott. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "EnhancedInputComponent.h"
#include "CS_PlayerController.generated.h"

class UCS_InputConfig;

/**
 * 
 */

UCLASS()
class CIRCUITRYSYSTEM_API ACS_PlayerController : public APlayerController
{
	GENERATED_BODY()

public:

	ACS_PlayerController();

	virtual void OnPossess(APawn* f_Pawn) override;
	
	void Move(const FInputActionValue& f_InputActionValue);
	
	void Look(const FInputActionValue& f_InputActionValue);

	/**
	 * Called via input to turn at a given rate.
	 * @param f_Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void TurnAtRate(float f_Rate);

	/**
	 * Called via input to turn look up/down at a given rate.
	 * @param f_Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void LookUpAtRate(float f_Rate);
	
	virtual void SetupInputComponent() override;
		
	/** The input config that maps Input Actions to Input Tags*/
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	UCS_InputConfig* InputConfig;
	
	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	float TurnRateGamepad;
};
