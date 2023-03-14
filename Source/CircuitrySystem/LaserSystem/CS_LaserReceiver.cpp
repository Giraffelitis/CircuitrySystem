// Copyright 2023 by Pace Abbott. All Rights Reserved.

#include "CS_LaserReceiver.h"
#include "CS_TaggingSystem.h"
#include "Macros.h"
#include "CircuitrySystem/PowerSystem/CS_PowerComponent.h"

// Sets default values
ACS_LaserReceiver::ACS_LaserReceiver()
{
	SceneComp = CreateDefaultSubobject<USceneComponent>("RootComponent");
	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>("BaseMesh");
	BaseMesh->SetupAttachment(SceneComp);

	PowerComp = CreateDefaultSubobject<UCS_PowerComponent>("PowerComp");
	TaggingSystemComp = CreateDefaultSubobject<UCS_TaggingSystem>("TaggingSystemComp");
}

void ACS_LaserReceiver::IsPowered_Implementation()
{
	if(!PowerComp->bIsPowered)
	{
		PowerComp->bIsPowered = true;

		AActor* AttachedParent = GetAttachParentActor();
		if(IsValid(AttachedParent))
		{
			if(AttachedParent->Implements<UCS_PoweredInterface>())
			{
				Execute_IsPowered(AttachedParent);
			}
		}
	}
}

void ACS_LaserReceiver::IsNotPowered_Implementation()
{
	if(PowerComp->bIsPowered)
	{
		PowerComp->bIsPowered = false;

		AActor* AttachedParent = GetAttachParentActor();
		if(AttachedParent->Implements<UCS_PoweredInterface>())
		{
			Execute_IsNotPowered(AttachedParent);
		}
	}
}
