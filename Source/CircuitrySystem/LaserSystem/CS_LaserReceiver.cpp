// Copyright 2023 by Pace Abbott. All Rights Reserved.


#include "CS_LaserReceiver.h"
#include "EnvironmentQuery/EnvQueryTypes.h"

// Sets default values
ACS_LaserReceiver::ACS_LaserReceiver()
{
	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>("BaseMesh");
	RootComponent = BaseMesh;	
}

void ACS_LaserReceiver::IsPowered_Implementation()
{
	if(!bIsPowered)
		IsReceivingPower.Broadcast();
}
