// Copyright 2023 by Pace Abbott. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "EnhancedInputComponent.h"
#include "InputAction.h"
#include "CS_InputConfig.h"
#include "GameplayTagContainer.h"
#include "CS_EnhancedInputComponent.generated.h"

/**
 *	Header only nothing added to .cpp
 *	Creates template to be used in other files as a method to Bind Actions using GameplayTags
 */

UCLASS()
class CIRCUITRYSYSTEM_API UCS_EnhancedInputComponent : public UEnhancedInputComponent
{
	GENERATED_BODY()

public:

	template<class UserClass, typename FuncType>
	void BindActionByTag(const UCS_InputConfig* InputConfig, const FGameplayTag& InputTag, ETriggerEvent TriggerEvent, UserClass* Object, FuncType Func);
};

template<class UserClass, typename FuncType>
void UCS_EnhancedInputComponent::BindActionByTag(const UCS_InputConfig* InputConfig, const FGameplayTag& InputTag, ETriggerEvent TriggerEvent, UserClass* Object, FuncType Func)
{
	check(InputConfig);
	if (const UInputAction* IA = InputConfig->FindInputActionForTag(InputTag))
	{
		BindAction(IA, TriggerEvent, Object, Func);
	}
}
