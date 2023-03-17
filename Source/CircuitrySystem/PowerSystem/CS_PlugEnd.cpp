// Copyright 2023 by Pace Abbott. All Rights Reserved.


#include "CS_PlugEnd.h"

#include "CS_PowerableBase.h"
#include "CS_PowerCable.h"
#include "CS_PowerComponent.h"
#include "CS_TaggingSystem.h"


// Sets default values
ACS_PlugEnd::ACS_PlugEnd()
{
	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>("BaseMesh");
	
	TaggingSystemComp = CreateDefaultSubobject<UCS_TaggingSystem>("TaggingSystemComp");
	PowerComp = CreateDefaultSubobject<UCS_PowerComponent>("PowerComp");
}

void ACS_PlugEnd::BeginPlay()
{
	Super::BeginPlay();

	TaggingSystemComp->ActiveGameplayTags.AddTag(FGameplayTag::RequestGameplayTag("ItemTag.Pickup.Socketable"));
}

void ACS_PlugEnd::Destroyed()
{
	Super::Destroyed();
	PowerComp->ReceivingPowerFromArray.Empty();
	UpdateAttachedPowerState();
}

void ACS_PlugEnd::IsPowered_Implementation(AActor* f_Actor)
{
	PowerComp->ReceivingPowerFromArray.AddUnique(f_Actor);
	UpdateAttachedPowerState();	
}

void ACS_PlugEnd::IsNotPowered_Implementation(AActor* f_Actor)
{
	PowerComp->ReceivingPowerFromArray.Remove(f_Actor);
	UpdateAttachedPowerState();	
}

void ACS_PlugEnd::CheckPoweredState_Implementation()
{
	Super::CheckPoweredState_Implementation();
	UpdateAttachedPowerState();
}

void ACS_PlugEnd::UpdateAttachedPowerState()
{
	/**	Check if plug is a giver or a receiver of power
	**	Giver if its receiving power from its attached cable
	**	Receiver if its supplying power to its attached cable.
	**/
	
	if(TaggingSystemComp->ActiveGameplayTags.HasTag(FGameplayTag::RequestGameplayTag("ItemTag.Power.Giver")))
	{
		AActor* AttachedParent = this->GetAttachParentActor();
		if(IsValid(AttachedParent) && AttachedParent->Implements<UCS_PoweredInterface>())
		{
			if(PowerComp->ReceivingPowerFromArray.Num() > 0)
			{
				PowerComp->bIsPowered = true;
				Execute_IsPowered(AttachedParent, this);
			}
			else
			{
				PowerComp->bIsPowered = false;
				Execute_IsNotPowered(AttachedParent, this);
			}
		}
	}
	else if(TaggingSystemComp->ActiveGameplayTags.HasTag(FGameplayTag::RequestGameplayTag("ItemTag.Power.Receiver")))
	{
		TArray<AActor*> AttachedActors;
		this->GetAttachedActors(AttachedActors);
		for(AActor* AttachedActor : AttachedActors)
		{
			ACS_PowerCable* AttachedPowerCable = Cast<ACS_PowerCable>(AttachedActor);
			if(!IsValid(AttachedPowerCable)) continue;
			AttachedPowerCable->TaggingSystemComp->ActiveGameplayTags.AddTag(FGameplayTag::RequestGameplayTag("ItemTag.Power.Giver"));
			AttachedPowerCable->UpdateAttachedPowerState();
		}
	}
}
