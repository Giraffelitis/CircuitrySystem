// Copyright 2023 by Pace Abbott. All Rights Reserved.


#include "CS_PowerCable.h"

#include "CS_PowerComponent.h"

ACS_PowerCable::ACS_PowerCable()
{
	PowerComp = CreateDefaultSubobject<UCS_PowerComponent>("PowerComp");
}
