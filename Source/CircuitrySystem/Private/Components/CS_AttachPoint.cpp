// Copyright 2023 by Pace Abbott. All Rights Reserved.


#include "Components/CS_AttachPoint.h"
#include "Actors/CS_AttachableActor.h"
#include "Components/CS_TaggingSystem.h"
#include "EngineUtils.h" // ActorIterator
#include "PowerSystem/CS_PoweredInterface.h"
#include "Core/CS_NativeGameplayTagLibrary.h"

using namespace CS_NativeGameplayTagLibrary;


// Sets default values for this component's properties
UCS_AttachPoint::UCS_AttachPoint()
{
	PrimaryComponentTick.bCanEverTick = true;
	TagComp = CreateDefaultSubobject<UCS_TaggingSystem>("TaggingSystemComp");
}

// Called when the game starts
void UCS_AttachPoint::BeginPlay()
{
	Super::BeginPlay();
	TagComp->ActiveGameplayTags.AddTag(ItemTag_Attach_Point);

	/*********************************************************************/
	// TODO:: Only run timer when Item is attachable item is being carried 
	/*********************************************************************/
	StartAttachableActorTimer();
}

//Start timer for AttachPoint checks
void UCS_AttachPoint::StartAttachableActorTimer()
{
	GetWorld()->GetTimerManager().SetTimer(DetectAttachableTimerHandle, this, &UCS_AttachPoint::DetectAttachableActors, MaxDetectAttachableTime, true);
}

//Cancel timer for AttachPoint checks
void UCS_AttachPoint::CancelAttachableActorTimer()
{
	GetWorld()->GetTimerManager().ClearTimer(DetectAttachableTimerHandle);
}

//Check within SearchRadius around the AttachPoint location and attach or detach accordingly
void UCS_AttachPoint::DetectAttachableActors()
{
	constexpr int SearchRadius = 20.0f;
	
	for(TActorIterator<ACS_AttachableActor> ActorItr(GetWorld()); ActorItr; ++ActorItr)
	{
		ACS_AttachableActor* AttachActor = *ActorItr;
		if(FVector::Distance(AttachActor->GetActorLocation(), this->GetComponentLocation()) < SearchRadius)
		{
			OnAttachActor(AttachActor);
			AttachedActor = AttachActor;
			CancelAttachableActorTimer();
		}
		else
		{
			if(AttachedActor == AttachActor)
			{
				OnDetachActor(AttachActor);
			}
		}
	}
}

//Gets AttachableActor in range and attaches it to socket of AttachPoint
void UCS_AttachPoint::OnAttachActor(ACS_AttachableActor* f_AttachActor)
{
	if(TagComp->ActiveGameplayTags.HasTag(ItemTag_Attach_Used)) return;
	UCS_TaggingSystem* OtherActorTags =  Cast<UCS_TaggingSystem>(f_AttachActor->GetComponentByClass(UCS_TaggingSystem::StaticClass()));
	if(!IsValid(OtherActorTags)) return;
	
	/***********************************************************************************************/
	//TODO:: Broadcast to Display prompt to attach to actor and bind delegate reply to attach actor.
	/***********************************************************************************************/
	
	UActorComponent* ActorComp = f_AttachActor->GetComponentByClass(UStaticMeshComponent::StaticClass());
	UStaticMeshComponent* MeshComp = Cast<UStaticMeshComponent>(ActorComp);
	MeshComp->SetSimulatePhysics(false);
	f_AttachActor->AttachToComponent(this, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
	AttachedActor = f_AttachActor;
	TagComp->ActiveGameplayTags.AddTag(ItemTag_Attach_Used);
	if(f_AttachActor->GetClass() == ACS_AttachableActor::StaticClass())
	{
		f_AttachActor->UpdateAttachedState(this, false);
	}
	if(f_AttachActor->Implements<UCS_PoweredInterface>())
	{
		ICS_PoweredInterface::Execute_CheckPoweredState(f_AttachActor);
		AttachPointUpdate.Broadcast(true, f_AttachActor);
	}
}

//Detaches AttachableActor from socket of Attach point
void UCS_AttachPoint::OnDetachActor(ACS_AttachableActor* f_AttachActor)
{
	f_AttachActor->bIsAttached = false;
	if(TagComp->ActiveGameplayTags.HasTag(ItemTag_Attach_Used))
	{
		TagComp->ActiveGameplayTags.RemoveTag(ItemTag_Attach_Used);
	}
	if(AttachedActor == f_AttachActor)
	{
		AttachedActor = nullptr;
	}
	if(f_AttachActor->GetClass() == ACS_AttachableActor::StaticClass())
		f_AttachActor->UpdateAttachedState(this, false);	
	
	if(f_AttachActor->Implements<UCS_PoweredInterface>())
		ICS_PoweredInterface::Execute_CheckPoweredState(f_AttachActor);
	AttachPointUpdate.Broadcast(false, f_AttachActor);
}

