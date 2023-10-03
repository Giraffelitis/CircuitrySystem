// Copyright 2023 by Pace Abbott. All Rights Reserved.


#include "Components/CS_ISMComponent.h"
#include "Components/CS_TaggingSystem.h"

UCS_ISMComponent::UCS_ISMComponent()
{
	TaggingSystem = CreateDefaultSubobject<UCS_TaggingSystem>("TaggingSystem");
}
