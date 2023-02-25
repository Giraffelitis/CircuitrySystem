// Copyright 2023 by Pace Abbott. All Rights Reserved.


#include "CS_InputConfig.h"
#include "GameplayTagContainer.h"
#include "EnhancedInput/Public/InputAction.h"

const UInputAction* UCS_InputConfig::FindInputActionForTag(const FGameplayTag& InputTag) const
{
	for (const FTaggedInputAction& TaggedInputAction : TaggedInputActions)
	{
		if (TaggedInputAction.InputAction && TaggedInputAction.InputTag == InputTag)
		{
			return TaggedInputAction.InputAction;
		}
	}

	return nullptr;
}