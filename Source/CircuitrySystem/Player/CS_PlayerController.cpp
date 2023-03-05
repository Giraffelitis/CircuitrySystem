// Copyright 2023 by Pace Abbott. All Rights Reserved.


#include "CS_PlayerController.h"
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
	CSEnhancedInputComponent->BindActionByTag(InputConfig, GameplayTags.InputTag_Move, ETriggerEvent::Triggered, this, &ACS_PlayerController::Move);
	CSEnhancedInputComponent->BindActionByTag(InputConfig, GameplayTags.InputTag_Look_Mouse, ETriggerEvent::Triggered, this, &ACS_PlayerController::Look);
	CSEnhancedInputComponent->BindActionByTag(InputConfig, GameplayTags.InputTag_Look_Stick, ETriggerEvent::Triggered, this, &ACS_PlayerController::Look);
}

void ACS_PlayerController::OnPossess(APawn* f_Pawn)
{
	Super::OnPossess(f_Pawn);
}

void ACS_PlayerController::Move(const FInputActionValue& f_InputActionValue)
{
	if (this != nullptr)
	{
		const FVector2D MoveValue = f_InputActionValue.Get<FVector2D>();
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

void ACS_PlayerController::Look(const FInputActionValue& f_InputActionValue)
{
	const FVector2D LookValue = f_InputActionValue.Get<FVector2D>();

	if (LookValue.X != 0.0f)
	{
		TurnAtRate(LookValue.X);
	}

	if (LookValue.Y != 0.0f)
	{
		LookUpAtRate(LookValue.Y);
	}
}

void ACS_PlayerController::TurnAtRate(float _Rate)
{
	// calculate delta for this frame from the rate information
	GetPawn()->AddControllerYawInput(_Rate * TurnRateGamepad * GetWorld()->GetDeltaSeconds());
}

void ACS_PlayerController::LookUpAtRate(float _Rate)
{
	// calculate delta for this frame from the rate information
	GetPawn()->AddControllerPitchInput(_Rate * TurnRateGamepad * GetWorld()->GetDeltaSeconds());
}



