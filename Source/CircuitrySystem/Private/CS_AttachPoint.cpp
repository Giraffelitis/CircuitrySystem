// Copyright 2023 by Pace Abbott. All Rights Reserved.


#include "CS_AttachPoint.h"
#include "CS_AttachableActor.h"
#include "CS_TaggingSystem.h"
#include "Macros.h"
#include "EngineUtils.h" // ActorIterator
#include "CircuitrySystem/PowerSystem/CS_PoweredInterface.h"
#include "Components/SphereComponent.h"

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
	TagComp->ActiveGameplayTags.AddTag(FGameplayTag::RequestGameplayTag("ItemTag.Attach.Point"));
	
	StartAttachableActorTimer();
}

void UCS_AttachPoint::StartAttachableActorTimer()
{
	GetWorld()->GetTimerManager().SetTimer(DetectAttachableTimerHandle, this, &UCS_AttachPoint::DetectAttachableActors, MaxDetectAttachableTime, true);
}

void UCS_AttachPoint::DetectAttachableActors()
{	
	for(TActorIterator<ACS_AttachableActor> ActorItr(GetWorld()); ActorItr; ++ActorItr)
	{
		ACS_AttachableActor* AttachActor = *ActorItr;
		if(FVector::Distance(AttachActor->GetActorLocation(), this->GetComponentLocation()) < 20.0f)
		{
			OnAttachActor(AttachActor);
			AttachedActor = AttachActor;
		}
		else
		{
			if(AttachedActor == AttachActor)
			{
				OnUnattachActor(AttachActor);
			}
		}
	}
}

void UCS_AttachPoint::OnAttachActor(ACS_AttachableActor* f_AttachActor)
{
	if(TagComp->ActiveGameplayTags.HasTag(FGameplayTag::RequestGameplayTag("ItemTag.Attach.Used"))) return;
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
	TagComp->ActiveGameplayTags.AddTag(FGameplayTag::RequestGameplayTag("ItemTag.Attach.Used"));
	if(f_AttachActor->GetClass() == ACS_AttachableActor::StaticClass())
		f_AttachActor->UpdateAttachedState(this, false);
	if(f_AttachActor->Implements<UCS_PoweredInterface>())
		ICS_PoweredInterface::Execute_CheckPoweredState(f_AttachActor);
	AttachPointUpdate.Broadcast(true, f_AttachActor);
}

void UCS_AttachPoint::OnUnattachActor(ACS_AttachableActor* f_AttachActor)
{
	f_AttachActor->bIsAttached = false;
	if(TagComp->ActiveGameplayTags.HasTag(FGameplayTag::RequestGameplayTag("ItemTag.Attach.Used")))
	{
		TagComp->ActiveGameplayTags.RemoveTag(FGameplayTag::RequestGameplayTag("ItemTag.Attach.Used"));
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

