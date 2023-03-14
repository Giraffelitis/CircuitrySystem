// Copyright 2023 by Pace Abbott. All Rights Reserved.


#include "CS_PowerBlock.h"
#include "CS_PowerComponent.h"
#include "Macros.h"
#include "Sockets.h"
#include "Engine/StaticMeshSocket.h"

ACS_PowerBlock::ACS_PowerBlock()
{
	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>("BaseMesh");
	RootComponent = BaseMesh;

	PowerComp = CreateDefaultSubobject<UCS_PowerComponent>("PowerComp");
	TaggingSystemComp = CreateDefaultSubobject<UCS_TaggingSystem>("TaggingSystemComp");
}

void ACS_PowerBlock::BeginPlay()
{
	Super::BeginPlay();

	SocketsArray = BaseMesh->GetAllSocketNames();
}

void ACS_PowerBlock::UpdatedPower()
{
	TArray<AActor*> AttachedActors;
	this->GetAttachedActors(AttachedActors);
	for(auto AttachedActor : AttachedActors)
	{
		
		if(!IsValid(AttachedActor))
			return;
		if(PowerComp->bIsPowered && AttachedActor->Implements<UCS_PoweredInterface>())
		{
			Execute_IsPowered(AttachedActor);
		}
		else if (!PowerComp->bIsPowered && AttachedActor->Implements<UCS_PoweredInterface>())
		{
			Execute_IsNotPowered(AttachedActor);
		}
	}
}

void ACS_PowerBlock::IsPowered_Implementation()
{;
	if(!PowerComp->bIsPowered)
	{
		PowerComp->bIsPowered = true;
		UpdatedPower();
	}
}

void ACS_PowerBlock::IsNotPowered_Implementation()
{
	if(PowerComp->bIsPowered)
	{
		PowerComp->bIsPowered = false;
		UpdatedPower();
	}
}

void ACS_PowerBlock::CheckPoweredState_Implementation()
{
	UpdatedPower();
}
