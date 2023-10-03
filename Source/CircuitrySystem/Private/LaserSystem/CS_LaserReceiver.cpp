// Copyright 2023 by Pace Abbott. All Rights Reserved.

#include "LaserSystem/CS_LaserReceiver.h"
#include "Components/CS_TaggingSystem.h"
#include "Macros.h"
#include "PowerSystem/CS_PowerComponent.h"
#include "Core/CS_NativeGameplayTagLibrary.h"

using namespace CS_NativeGameplayTagLibrary;


// Sets default values
ACS_LaserReceiver::ACS_LaserReceiver()
{
	SceneComp = CreateDefaultSubobject<USceneComponent>("RootComponent");
	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>("BaseMesh");
	BaseMesh->SetupAttachment(SceneComp);

	PowerComp = CreateDefaultSubobject<UCS_PowerComponent>("PowerComp");
	TaggingSystemComp = CreateDefaultSubobject<UCS_TaggingSystem>("TaggingSystemComp");
}

void ACS_LaserReceiver::BeginPlay()
{
	Super::BeginPlay();
	TaggingSystemComp->ActiveGameplayTags.AddTag(ItemTag_Power_Giver);
}

void ACS_LaserReceiver::IsPowered_Implementation(AActor* f_Actor)
{
	PowerComp->ReceivingPowerFromArray.AddUnique(f_Actor);
	UpdateAttachedPowerState();	
}

void ACS_LaserReceiver::IsNotPowered_Implementation(AActor* f_Actor)
{
	PowerComp->ReceivingPowerFromArray.Remove(f_Actor);
	UpdateAttachedPowerState();	
}

void ACS_LaserReceiver::UpdateAttachedPowerState()
{
	AActor* AttachedParent = this->GetAttachParentActor();
	
	if(IsValid(AttachedParent) && AttachedParent->Implements<UCS_PoweredInterface>())
	{
		if(PowerComp->ReceivingPowerFromArray.Num() > 0)
		{
			if(!PowerComp->bIsPowered)
			{
				PowerComp->bIsPowered = true;
				Execute_IsPowered(AttachedParent, this);
			}
		}
		else
		{
			if(PowerComp->bIsPowered)
			{
				PowerComp->bIsPowered = false;
				Execute_IsNotPowered(AttachedParent, this);
			}
		}
	}
}