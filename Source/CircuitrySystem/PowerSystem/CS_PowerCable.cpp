// Copyright 2023 by Pace Abbott. All Rights Reserved.


#include "CS_PowerCable.h"
#include "CableComponent.h"
#include "ComponentUtils.h"
#include "CS_PlugEnd.h"
#include "CS_PowerableBase.h"
#include "CS_PowerComponent.h"
#include "CS_TaggingSystem.h"

ACS_PowerCable::ACS_PowerCable()
{
	PlugEnd_A = CreateDefaultSubobject<UStaticMeshComponent>("PlugEnd_A");
	RootComponent = PlugEnd_A;
	CableComp = CreateDefaultSubobject<UCableComponent>("CableComp");
	CableComp->SetupAttachment(PlugEnd_A);

	TaggingSystemComp = CreateDefaultSubobject<UCS_TaggingSystem>("TaggingSystemComp");
	PowerComp = CreateDefaultSubobject<UCS_PowerComponent>("PowerComp");
}

void ACS_PowerCable::BeginPlay()
{
	Super::BeginPlay();
	
	CableMesh = CableComp;
	TaggingSystemComp->ActiveGameplayTags.AddTag(FGameplayTag::RequestGameplayTag("ItemTag.Pickup.Socketable"));
	TaggingSystemComp->ActiveGameplayTags.AddTag(FGameplayTag::RequestGameplayTag("ItemTag.Power.Receiver"));
	UpdateAttachedPowerState();	
}

void ACS_PowerCable::Destroyed()
{
	Super::Destroyed();

	PlugEnd_B->Destroy();
}

void ACS_PowerCable::SpawnPlugB()
{
	PlugEnd_B = Cast<ACS_PlugEnd>(GetWorld()->SpawnActor(PlugEnd_BClass));
	FVector ActorLocation = GetActorLocation();
	float Offset = 50.0f;
	PlugEnd_B->SetActorLocation(ActorLocation + (this->GetActorUpVector().Z + Offset));
	CableComp->SetAttachEndTo(PlugEnd_B, "BaseMesh", "Plug_B_0");
}

void ACS_PowerCable::IsPowered_Implementation(AActor* f_Actor)
{
	PowerComp->ReceivingPowerFromArray.AddUnique(f_Actor);
	TaggingSystemComp->ActiveGameplayTags.AddTag(FGameplayTag::RequestGameplayTag("ItemTag.Power.Receiver"));
	UpdateAttachedPowerState();
}

void ACS_PowerCable::IsNotPowered_Implementation(AActor* f_Actor)
{
	PowerComp->ReceivingPowerFromArray.Remove(f_Actor);
	UpdateAttachedPowerState();
	TaggingSystemComp->ActiveGameplayTags.AddTag(FGameplayTag::RequestGameplayTag("ItemTag.Power.Receiver"));
}

void ACS_PowerCable::CheckPoweredState_Implementation()
{
	Super::CheckPoweredState_Implementation();
	if(!bIsAttached && TaggingSystemComp->ActiveGameplayTags.HasTag(FGameplayTag::RequestGameplayTag("ItemTag.Power.Receiver")))
	{
		PowerComp->ReceivingPowerFromArray.Empty();
		UpdateAttachedPowerState();	
		TaggingSystemComp->ActiveGameplayTags.RemoveTag(FGameplayTag::RequestGameplayTag("ItemTag.Power.Receiver"));
	}
}

void ACS_PowerCable::UpdateAttachedPowerState()
{
	/**  ItemTag.Power.Receiver means it is receiving power from another object
	 **  ItemTag.Power.Giver means it is giving power to another object
	 **  Since a plug can reveive power or give power to the cable and vice versa we need to check 
	 **  Where its power is coming from before the cable tells it to update. 
	 **/
	if(TaggingSystemComp->ActiveGameplayTags.HasTag(FGameplayTag::RequestGameplayTag("ItemTag.Power.Receiver")))
	{
		UpdatePlugPower();
	}
	else if (TaggingSystemComp->ActiveGameplayTags.HasTag(FGameplayTag::RequestGameplayTag("ItemTag.Power.Giver")))
	{
		UpdateAttachedToPower();
	}
	UpdateMesh();
}

void ACS_PowerCable::UpdatePlugPower()
{
	if(PowerComp->ReceivingPowerFromArray.Num() > 0)
	{
		PowerComp->bIsPowered = true;
		if(!IsValid(PlugEnd_B)) return;

		//Check if plug is already receiving power from somewhere else if not give it power
		if(!PlugEnd_B->TaggingSystemComp->ActiveGameplayTags.HasTag(FGameplayTag::RequestGameplayTag("ItemTag.Power.Receiver")))
		{
			PlugEnd_B->TaggingSystemComp->ActiveGameplayTags.AddTag(FGameplayTag::RequestGameplayTag("ItemTag.Power.Giver"));
			Execute_IsPowered(PlugEnd_B, this);
		}
	}
	else
	{
		PowerComp->bIsPowered = false;
		if(!IsValid(PlugEnd_B)) return;

		// Check if plug is receiving power from cable (making it a giver of power to whatever it is attached to) then turn off
		if(PlugEnd_B->TaggingSystemComp->ActiveGameplayTags.HasTag(FGameplayTag::RequestGameplayTag("ItemTag.Power.Giver")))
		{
			Execute_IsNotPowered(PlugEnd_B, this);
			PlugEnd_B->TaggingSystemComp->ActiveGameplayTags.RemoveTag(FGameplayTag::RequestGameplayTag("ItemTag.Power.Giver"));
		}
	}
}

void ACS_PowerCable::UpdateAttachedToPower()
{
	ACS_PowerableBase* AttachedActor = Cast<ACS_PowerableBase>(GetAttachParentActor());
	if(!IsValid(AttachedActor)) return;

	if(PowerComp->ReceivingPowerFromArray.Num() > 0)
	{
		PowerComp->bIsPowered = true;
		Execute_IsPowered(AttachedActor, this);
	}
	else
	{
		PowerComp->bIsPowered = false;
		Execute_IsNotPowered(AttachedActor, this);
	}
	AttachedActor->UpdateAttachedPowerState();
}

void ACS_PowerCable::UpdateMesh()
{
	if(PowerComp->bIsPowered)
	{
		if(MaterialNotPowered && PowerComp->bIsPowered)
		{			
			CableMesh->SetMaterial(0,MaterialPowered);
		}
	}
	else if(MaterialPowered && !PowerComp->bIsPowered)
	{
		CableMesh->SetMaterial(0,MaterialNotPowered);
	}
}