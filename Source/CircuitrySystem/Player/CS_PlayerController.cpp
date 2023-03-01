// Copyright 2023 by Pace Abbott. All Rights Reserved.


#include "CS_PlayerController.h"
#include "CS_PlayerCharacter.h"
#include "CircuitrySystem/EIC/CS_EnhancedInputComponent.h"
#include "CircuitrySystem/GameBase/CS_GameplayTags.h"

ACS_PlayerController::ACS_PlayerController()
{
	// set our turn rates for input
	TurnRateGamepad = 45.f;
}

void ACS_PlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	
	check(InputComponent)
	UCS_EnhancedInputComponent* CSEnhancedInputComponent = Cast<UCS_EnhancedInputComponent>(InputComponent);

	//Make sure to set your input component class in the InputSettings->DefaultClasses
	if(!ensure(CSEnhancedInputComponent))
		return;	

	const FCS_GameplayTags& GameplayTags = FCS_GameplayTags::Get();

	//Bind Input actions by tag
	CSEnhancedInputComponent->BindActionByTag(InputConfig, GameplayTags.InputTag_Move, ETriggerEvent::Triggered, this, &ACS_PlayerController::Input_Move);
	CSEnhancedInputComponent->BindActionByTag(InputConfig, GameplayTags.InputTag_Look_Mouse, ETriggerEvent::Triggered, this, &ACS_PlayerController::Input_Look);
	CSEnhancedInputComponent->BindActionByTag(InputConfig, GameplayTags.InputTag_Look_Stick, ETriggerEvent::Triggered, this, &ACS_PlayerController::Input_Look);
	CSEnhancedInputComponent->BindActionByTag(InputConfig, GameplayTags.InputTag_Action_Pickup, ETriggerEvent::Triggered, this, &ACS_PlayerController::Input_Pickup);
	CSEnhancedInputComponent->BindActionByTag(InputConfig, GameplayTags.InputTag_Jump, ETriggerEvent::Triggered, this, &ACS_PlayerController::Input_Jump);
	CSEnhancedInputComponent->BindActionByTag(InputConfig, GameplayTags.InputTag_Action_Support_Primary, ETriggerEvent::Triggered, this, &ACS_PlayerController::Input_Primary_Support_Action);
	CSEnhancedInputComponent->BindActionByTag(InputConfig, GameplayTags.InputTag_Action_Support_Secondary, ETriggerEvent::Triggered, this, &ACS_PlayerController::Input_Secondary_Support_Action);

	CSEnhancedInputComponent->BindActionByTag(InputConfig, GameplayTags.InputTag_Modifier_Pressed, ETriggerEvent::Triggered, this, &ACS_PlayerController::Input_Modifier_Pressed);
	CSEnhancedInputComponent->BindActionByTag(InputConfig, GameplayTags.InputTag_Modifier_Released, ETriggerEvent::Triggered, this, &ACS_PlayerController::Input_Modifier_Released);	
}

void ACS_PlayerController::Input_Move(const FInputActionValue& InputActionValue)
{
	if (this != nullptr)
	{
		const FVector2D MoveValue = InputActionValue.Get<FVector2D>();
		const FRotator MovementRotation(0.0f, this->GetControlRotation().Yaw, 0.0f);

		if (MoveValue.X != 0.0f)
		{
			const FVector MovementDirection = MovementRotation.RotateVector(FVector::RightVector);
			GetPawn()->AddMovementInput(MovementDirection, MoveValue.X);
		}

		if (MoveValue.Y != 0.0f)
		{
			const FVector MovementDirection = MovementRotation.RotateVector(FVector::ForwardVector);
			GetPawn()->AddMovementInput(MovementDirection, MoveValue.Y);
		}
	}
}

void ACS_PlayerController::Input_Look(const FInputActionValue& InputActionValue)
{
	const FVector2D LookValue = InputActionValue.Get<FVector2D>();

	if (LookValue.X != 0.0f)
	{
		TurnAtRate(LookValue.X);
	}

	if (LookValue.Y != 0.0f)
	{
		LookUpAtRate(LookValue.Y);
	}
}

void ACS_PlayerController::Input_Jump(const FInputActionValue& InputActionValue)
{
	GetCharacter()->Jump();
}

void ACS_PlayerController::Input_Pickup(const FInputActionValue& InputActionValue)
{
	Cast<ACS_PlayerCharacter>(GetCharacter())->PickupAction();
}

void ACS_PlayerController::TurnAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	GetPawn()->AddControllerYawInput(Rate * TurnRateGamepad * GetWorld()->GetDeltaSeconds());
}

void ACS_PlayerController::LookUpAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	GetPawn()->AddControllerPitchInput(Rate * TurnRateGamepad * GetWorld()->GetDeltaSeconds());
}

/** Handles Primary Support Action */
void ACS_PlayerController::Input_Primary_Support_Action(const FInputActionValue& InputActionValue)
{
	Cast<ACS_PlayerCharacter>(GetCharacter())->PrimarySupportAction();
}

/** Handles Secondary Support Action */
void ACS_PlayerController::Input_Secondary_Support_Action(const FInputActionValue& InputActionValue)
{
	Cast<ACS_PlayerCharacter>(GetCharacter())->SecondarySupportAction();
}

/** Handles Input Modifier */
void ACS_PlayerController::Input_Modifier_Pressed(const FInputActionValue& InputActionValue)
{
	Cast<ACS_PlayerCharacter>(GetCharacter())->InputModifier = true;
}

/** Handles Input Modifier */
void ACS_PlayerController::Input_Modifier_Released(const FInputActionValue& InputActionValue)
{
	Cast<ACS_PlayerCharacter>(GetCharacter())->InputModifier = false;
}
