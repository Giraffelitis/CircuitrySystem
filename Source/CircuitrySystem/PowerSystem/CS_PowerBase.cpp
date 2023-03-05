// Copyright 2023 by Pace Abbott. All Rights Reserved.


#include "CS_PowerBase.h"

// Sets default values
ACS_PowerBase::ACS_PowerBase()
{
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


