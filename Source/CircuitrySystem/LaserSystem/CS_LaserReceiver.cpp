// Copyright 2023 by Pace Abbott. All Rights Reserved.

#include "CS_LaserReceiver.h"

// Sets default values
ACS_LaserReceiver::ACS_LaserReceiver()
{
	SceneComp = CreateDefaultSubobject<USceneComponent>("RootComponent");
	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>("BaseMesh");
	BaseMesh->SetupAttachment(SceneComp);
}

void ACS_LaserReceiver::IsPowered_Implementation()
{
	if(!bIsPowered)
		IsReceivingPower.Broadcast();

	bIsPowered = true;
}

void ACS_LaserReceiver::IsNotPowered_Implementation()
{
	if(bIsPowered)
		LostPower.Broadcast();

	bIsPowered = false;
}

