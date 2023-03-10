// Copyright 2023 by Pace Abbott. All Rights Reserved.


#include "CS_CircuitComponentBase.h"

#include "CS_ISMComponent.h"
#include "CS_TaggingSystem.h"
#include "GameplayTagContainer.h"
#include "Components/InstancedStaticMeshComponent.h"
#include "Macros.h"
#include "CircuitrySystem/LaserSystem/CS_LaserEmitter.h"
#include "CircuitrySystem/LaserSystem/CS_LaserReceiver.h"
#include "CircuitrySystem/PowerSystem/CS_PowerCable.h"
#include "EnvironmentQuery/EnvQueryTypes.h"

// Sets default values
ACS_CircuitComponentBase::ACS_CircuitComponentBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	CircuitBoardInstancedMesh = CreateDefaultSubobject<UCS_ISMComponent>("CircuitBoardInstancedMesh");
	RootComponent = CircuitBoardInstancedMesh;
	
	SocketBlockInstancedMesh = CreateDefaultSubobject<UCS_ISMComponent>("SocketBlockInstancedMesh");
	
	TaggingSystemComp = CreateDefaultSubobject<UCS_TaggingSystem>("TaggingSystemComp");
}

// Called when the game starts or when spawned
void ACS_CircuitComponentBase::BeginPlay()
{
	Super::BeginPlay();
	
	CircuitBoardInstancedMesh->AddInstance(FTransform());

	InstanceSocketsArray = CircuitBoardInstancedMesh->GetAllSocketNames();
	InstanceSocketsArray.Append(SocketBlockInstancedMesh->GetAllSocketNames());

}

void ACS_CircuitComponentBase::DestroyInstance(const FHitResult f_HitResult)
{
	if(f_HitResult.Item >= 0)
	{
		if(f_HitResult.GetComponent())
		{
			UInstancedStaticMeshComponent* HitInstance = Cast<UInstancedStaticMeshComponent>(f_HitResult.GetComponent());
			HitInstance->RemoveInstance(f_HitResult.Item);			
		}
	}
}

FTransform ACS_CircuitComponentBase::GetISMSocketTransform(UInstancedStaticMeshComponent* f_ISMComponent, int32 f_ISMIndex, const FName& f_SocketName)
{	
	if(f_ISMComponent && f_ISMComponent->IsValidInstance(f_ISMIndex))
	{
		FTransform ISMTransform = FTransform();
		f_ISMComponent->GetInstanceTransform(f_ISMIndex, ISMTransform, true);
		FTransform SocketTransform = f_ISMComponent->GetSocketTransform(f_SocketName, RTS_Component);
		ISMTransform = SocketTransform * ISMTransform;

		return ISMTransform;
	}

	return FTransform();
}

int ACS_CircuitComponentBase::GetHitISMComponentIndex(const FHitResult f_HitResult)
{
	//this function is currently being used. Leaving here to finish tutorial
	return f_HitResult.Item;
}

bool ACS_CircuitComponentBase::IsValidSocket(UInstancedStaticMeshComponent* f_HitComponent, const FName& f_Filter,
	const FName& f_SocketName)
{
	bool bSuccess = true;
	if(!f_HitComponent->DoesSocketExist(f_SocketName))
	{
		bSuccess = false;
		return bSuccess;
	}

	FString FilterString = f_Filter.ToString();
	FString SocketNameString = f_SocketName.ToString();

	if(!SocketNameString.Contains(FilterString, ESearchCase::CaseSensitive))
	{
		bSuccess = false;
	}
	return bSuccess;
}


FTransform ACS_CircuitComponentBase::GetHitSocketTransform(const FHitResult& f_HitResult, const FName& f_Filter, float f_ValidHitDistance)
{
	if(UInstancedStaticMeshComponent* HitComponent = Cast<UInstancedStaticMeshComponent>(f_HitResult.GetComponent()))
	{
		const int HitIndex = f_HitResult.Item;
	
		FTransform ClosestSocket = FTransform();
		if(HitIndex != -1)
		{
			float ClosestDistance = f_ValidHitDistance;
			for (const FName& SocketName : InstanceSocketsArray)
			{
				if(IsValidSocket(HitComponent, f_Filter, SocketName))
				{
					FTransform SocketTransform = GetISMSocketTransform(HitComponent, HitIndex, SocketName);
					if(FVector::Distance(SocketTransform.GetLocation(), f_HitResult.ImpactPoint) < ClosestDistance)
					{
						ClosestDistance = FVector::Distance(SocketTransform.GetLocation(), f_HitResult.ImpactPoint);
						ClosestSocket = SocketTransform;
					}
				}
			}
		}
		return ClosestSocket;
	}
	return FTransform();
}

void ACS_CircuitComponentBase::AddInstanceToActor(const FTransform& f_ActorTransform, ECircuitComponentType f_CircuitCompType, FGameplayTagContainer& f_BlockingTags)
{	
	switch (f_CircuitCompType)
	{
	case ECircuitComponentType::Base :
		{
			CircuitBoardInstancedMesh->TaggingSystem->BlockingTags.AppendTags(f_BlockingTags);
			CircuitBoardInstancedMesh->AddInstance(f_ActorTransform, true);
			break;
		}
	case ECircuitComponentType::PowerCable :
		{
			ACS_PowerCable* Cable = GetWorld()->SpawnActor<ACS_PowerCable>(PowerCable);
			//Cable->AttachToActor();
			break;
		}
	case ECircuitComponentType::Laser :
		{
			ACS_LaserEmitter* Emitter = GetWorld()->SpawnActor<ACS_LaserEmitter>(LaserEmitter);
			Emitter->SetActorTransform(f_ActorTransform);
			Emitter->TaggingSystemComp->ActiveGameplayTags.AddTag(FGameplayTag::RequestGameplayTag("BuildTag.Player"));
			break;
		}		
	case ECircuitComponentType::Receiver :
		{
			ACS_LaserReceiver* Receiver = GetWorld()->SpawnActor<ACS_LaserReceiver>(LaserReceiver);
			Receiver->SetActorTransform(f_ActorTransform);
			Receiver->TaggingSystemComp->ActiveGameplayTags.AddTag(FGameplayTag::RequestGameplayTag("BuildTag.Player"));
			break;
		}	
	case ECircuitComponentType::SocketBlock :
		{
			SocketBlockInstancedMesh->TaggingSystem->BlockingTags.AppendTags(f_BlockingTags);
			SocketBlockInstancedMesh->AddInstance(f_ActorTransform, true);
			break;
		}
		
	case ECircuitComponentType::Switch : CircuitBoardInstancedMesh->AddInstance(f_ActorTransform, true); break;	
	default : break;
	}
}
