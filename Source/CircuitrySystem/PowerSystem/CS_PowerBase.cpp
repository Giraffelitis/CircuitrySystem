// Copyright 2023 by Pace Abbott. All Rights Reserved.


#include "CS_PowerBase.h"

#include "CS_PowerComponent.h"

// Sets default values
ACS_PowerBase::ACS_PowerBase()
{
	PowerComponent = CreateDefaultSubobject<UCS_PowerComponent>("PowerComp");
}

void ACS_PowerBase::IsPowered_Implementation()
{
	HasPower();
}


