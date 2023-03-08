// Copyright 2023 by Pace Abbott. All Rights Reserved.


#include "CS_PowerBase.h"

#include "CS_TaggingSystem.h"

// Sets default values
ACS_PowerBase::ACS_PowerBase()
{
	TaggingSystemComp = CreateDefaultSubobject<UCS_TaggingSystem>("TaggingSystemComp");
}

void ACS_PowerBase::IsPowered_Implementation()
{
	if(!bIsPowered)
	{
		HasPower();
		bIsPowered = true;
	}
}

void ACS_PowerBase::IsNotPowered_Implementation()
{
	if(bIsPowered)
	{
		LostPower();
		bIsPowered = false;
	}
}


