// Copyright 2023 by Pace Abbott. All Rights Reserved.


#include "CS_AttachableActor.h"
#include "CS_AttachPoint.h"

void ACS_AttachableActor::Destroyed()
{
	Super::Destroyed();	

	TArray<UActorComponent*> ActorComponents;
	AActor* AttachParent = GetAttachParentActor();
	if(!IsValid(AttachParent)) return;
	AttachParent->GetComponents(ActorComponents);
	for(UActorComponent* ActorComp : ActorComponents)
	{
		UCS_AttachPoint* AttachPoint = Cast<UCS_AttachPoint>( ActorComp);
		if(IsValid(AttachPoint))
		{
			AttachPoint->OnUnattachActor(this);	
		}
	}
}
void ACS_AttachableActor::UpdateAttachedState(UCS_AttachPoint* f_AttachPoint, bool f_bIsAttached)
{
	bIsAttached = f_bIsAttached;
	AttachedToActor = f_AttachPoint->GetAttachParentActor();
}

