// Copyright 2023 by Pace Abbott. All Rights Reserved.


#include "CS_BuildCircuitISM.h"
#include "CS_ISMComponent.h"
#include "CS_TaggingSystem.h"
#include "GameplayTagContainer.h"
#include "Components/InstancedStaticMeshComponent.h"
#include "Macros.h"

// Sets default values
ACS_BuildCircuitISM::ACS_BuildCircuitISM()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	CircuitBoardInstancedMesh = CreateDefaultSubobject<UCS_ISMComponent>("CircuitBoardInstancedMesh");
	RootComponent = CircuitBoardInstancedMesh;
	BuildCircuitBase = CreateDefaultSubobject<ACS_BuildCircuitBase>("BuildCircuitBase");
	TaggingSystemComp = CreateDefaultSubobject<UCS_TaggingSystem>("TaggingSystemComp");
}

// Called when the game starts or when spawned
void ACS_BuildCircuitISM::BeginPlay()
{
	Super::BeginPlay();
	
	CircuitBoardInstancedMesh->AddInstance(FTransform());

	GenerateSocketArray();
}

void ACS_BuildCircuitISM::GenerateSocketArray()
{
	BuildCircuitBase->InstanceSocketsArray = CircuitBoardInstancedMesh->GetAllSocketNames();
}

void ACS_BuildCircuitISM::DestroyInstance(const FHitResult f_HitResult)
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

FTransform ACS_BuildCircuitISM::GetISMSocketTransform(UInstancedStaticMeshComponent* f_ISMComponent, int32 f_ISMIndex, const FName& f_SocketName)
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

int ACS_BuildCircuitISM::GetHitISMComponentIndex(const FHitResult f_HitResult)
{
	//this function is currently being used. Leaving here to finish tutorial
	return f_HitResult.Item;
}

bool ACS_BuildCircuitISM::IsValidSocket(const FHitResult& f_HitResult, const FName& f_Filter,
	const FName& f_SocketName)
{
	bool bSuccess = true;
	if(UInstancedStaticMeshComponent* HitComponent = Cast<UInstancedStaticMeshComponent>(f_HitResult.GetComponent()))
	{
		if(!HitComponent->DoesSocketExist(f_SocketName))
		{
			bSuccess = false;
			return bSuccess;
		}
	}

	FString FilterString = f_Filter.ToString();
	FString SocketNameString = f_SocketName.ToString();

	if(!SocketNameString.Contains(FilterString, ESearchCase::CaseSensitive))
	{
		bSuccess = false;
	}
	return bSuccess;
}


FTransform ACS_BuildCircuitISM::GetHitInstanceSocketTransform(const FHitResult& f_HitResult, const FName& f_Filter, float f_ValidHitDistance)
{
	if(UInstancedStaticMeshComponent* HitComponent = Cast<UInstancedStaticMeshComponent>(f_HitResult.GetComponent()))
	{
		const int HitIndex = f_HitResult.Item;
	
		FTransform ClosestSocket = FTransform();
		if(HitIndex != -1)
		{
			float ClosestDistance = f_ValidHitDistance;
			for (const FName& SocketName : BuildCircuitBase->InstanceSocketsArray)
			{
				if(IsValidSocket(f_HitResult, f_Filter, SocketName))
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

void ACS_BuildCircuitISM::AddInstanceToActor(const FTransform& f_ActorTransform, ECircuitComponentType f_CircuitCompType, FGameplayTagContainer& f_BlockingTags)
{	
	switch (f_CircuitCompType)
	{
	case ECircuitComponentType::Base :
		{
			CircuitBoardInstancedMesh->TaggingSystem->BlockingTags.AppendTags(f_BlockingTags);
			CircuitBoardInstancedMesh->AddInstance(f_ActorTransform, true);
			break;
		}
		
	default : break;
	}
}
