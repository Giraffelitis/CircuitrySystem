// Copyright 2023 by Pace Abbott. All Rights Reserved.


#include "PowerSystem/CS_PowerableBase.h"
#include "Components/CS_AttachPoint.h"
#include "Components/CS_TaggingSystem.h"
#include "Macros.h"
#include "Core/CS_NativeGameplayTagLibrary.h"
#include "PowerSystem/CS_PowerComponent.h"

using namespace CS_NativeGameplayTagLibrary;

// Sets default values
ACS_PowerableBase::ACS_PowerableBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>("BaseMesh");
	RootComponent = BaseMesh;
	AttachPoint_0 = CreateDefaultSubobject<UCS_AttachPoint>("AttachPoint_0");
	AttachPoint_0->SetupAttachment(BaseMesh);

	PowerComp = CreateDefaultSubobject<UCS_PowerComponent>("PowerComp");
	TaggingSystemComp = CreateDefaultSubobject<UCS_TaggingSystem>("TaggingSystemComp");

}

void ACS_PowerableBase::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	
	GetComponents<UCS_AttachPoint>(AttachPoints);
	for(UCS_AttachPoint* AttachPoint : AttachPoints)
	{
		BindtoAPDelegates(AttachPoint);
	}
}

void ACS_PowerableBase::BeginPlay()
{
	Super::BeginPlay();
}

void ACS_PowerableBase::Destroyed()
{
	Super::Destroyed();
	
	TArray<AActor*> AttachedActors;
	this->GetAttachedActors(AttachedActors);
	for(auto AttachedActor : AttachedActors)
	{
		AttachedActor->Destroy();
	}
}

void ACS_PowerableBase::BindtoAPDelegates(UCS_AttachPoint* f_AttachPoint)
{
	f_AttachPoint->AttachPointUpdate.AddUObject(this, &ThisClass::UpdateAttachedState);
}

void ACS_PowerableBase::UpdateAttachedState(bool f_bIsAttached, AActor* f_AttachActor)
{
	if(!f_bIsAttached)
	{
		PowerComp->ReceivingPowerFromArray.Remove(f_AttachActor);
		UpdateAttachedPowerState();	
	}
	else
	{
		UpdateAttachedPowerState();	
	}
}

//Add actor to powered array 
void ACS_PowerableBase::IsPowered_Implementation(AActor* f_Actor)
{
	PowerComp->ReceivingPowerFromArray.AddUnique(f_Actor);
	UpdateAttachedPowerState();	
}

//Remove Actor from powered array
void ACS_PowerableBase::IsNotPowered_Implementation(AActor* f_Actor)
{
	PowerComp->ReceivingPowerFromArray.Remove(f_Actor);
	UpdateAttachedPowerState();	
}

void ACS_PowerableBase::CheckPoweredState_Implementation()
{
	UpdateAttachedPowerState();
}

void ACS_PowerableBase::UpdateAttachedPowerState()
{
	if(PowerComp->ReceivingPowerFromArray.Num() > 0)
	{
		PowerComp->bIsPowered = true;
	}
	else
	{
		PowerComp->bIsPowered = false;
	}
	
	TArray<AActor*> AttachedActors;
	this->GetAttachedActors(AttachedActors);
	for(auto AttachedActor : AttachedActors)
	{
		if(!IsValid(AttachedActor))
			return;
		UActorComponent* ActorComp = AttachedActor->GetComponentByClass(UCS_TaggingSystem::StaticClass());
		if(!IsValid(ActorComp)) return;
		UCS_TaggingSystem* TagComp = Cast<UCS_TaggingSystem>(ActorComp);
		if(!IsValid(TagComp)) return;
		
		if(!TagComp->ActiveGameplayTags.HasTag(ItemTag_Power_Giver))
		{
			if(PowerComp->bIsPowered && AttachedActor->Implements<UCS_PoweredInterface>())
			{
				Execute_IsPowered(AttachedActor, this);
			}
			else if (!PowerComp->bIsPowered && AttachedActor->Implements<UCS_PoweredInterface>())
			{
				Execute_IsNotPowered(AttachedActor, this);
			}
		}
	}
}



