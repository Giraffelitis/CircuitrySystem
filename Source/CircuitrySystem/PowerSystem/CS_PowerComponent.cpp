// Copyright 2023 by Pace Abbott. All Rights Reserved.


#include "CS_PowerComponent.h"

#include "ComponentUtils.h"
#include "Macros.h"

// Sets default values for this component's properties


void UCS_PowerComponent::IsPowered_Implementation()
{
#if !UE_BUILD_SHIPPING
	PRINT(-1, 5.0f, FColor::Black, "Is Powered");
#endif
}
