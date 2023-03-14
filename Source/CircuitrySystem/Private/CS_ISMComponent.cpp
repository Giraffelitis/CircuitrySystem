// Copyright 2023 by Pace Abbott. All Rights Reserved.


#include "CS_ISMComponent.h"
#include "CS_TaggingSystem.h"

UCS_ISMComponent::UCS_ISMComponent()
{
	TaggingSystem = CreateDefaultSubobject<UCS_TaggingSystem>("TaggingSystem");
}
