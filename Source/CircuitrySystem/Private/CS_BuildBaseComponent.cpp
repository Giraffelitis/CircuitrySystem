// Copyright 2023 by Pace Abbott. All Rights Reserved.


#include "CS_BuildBaseComponent.h"

#include "Components/InstancedStaticMeshComponent.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
ACS_BuildBaseComponent::ACS_BuildBaseComponent()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	CircuitBoardInstancedMesh = CreateDefaultSubobject<UInstancedStaticMeshComponent>("CircuitBoardInstancedMesh");
	RootComponent = CircuitBoardInstancedMesh;

	SocketBlockInstancedMesh = CreateDefaultSubobject<UInstancedStaticMeshComponent>("SocketBlockInstancedMesh");
}

// Called when the game starts or when spawned
void ACS_BuildBaseComponent::BeginPlay()
{
	Super::BeginPlay();
	
	CircuitBoardInstancedMesh->AddInstance(FTransform());

}

void ACS_BuildBaseComponent::DestroyInstance(FVector f_HitPoint)
{
	const TArray<int32> HitIndexes = CircuitBoardInstancedMesh->GetInstancesOverlappingSphere(f_HitPoint, 1.0f);

	if(HitIndexes.Num() > 0)
	{
		CircuitBoardInstancedMesh->RemoveInstance(HitIndexes[0]);
	}
}

FTransform ACS_BuildBaseComponent::GetISMSocketTransform(UInstancedStaticMeshComponent* f_ISMComponent, int32 f_ISMIndex, const FName& f_SocketName, bool& f_Success, bool f_WorldSpace)
{
	f_Success = true;
	
	if(f_ISMComponent && f_ISMComponent->IsValidInstance(f_ISMIndex))
	{
		FTransform ISMTransform = FTransform();
		f_ISMComponent->GetInstanceTransform(f_ISMIndex, ISMTransform, false);
		FTransform SocketTransform = f_ISMComponent->GetSocketTransform(f_SocketName, RTS_Component);
		if(SocketTransform.Equals(FTransform()))
		{
			f_Success = false;
			
			return FTransform();
		}
		FTransform RelativeTransform = UKismetMathLibrary::MakeRelativeTransform(SocketTransform, ISMTransform);
		FVector RelativeLocation = RelativeTransform.GetLocation();
		if(f_WorldSpace)
		{
			RelativeLocation.Z = SocketTransform.GetLocation().Z;
			f_ISMComponent->GetInstanceTransform(f_ISMIndex, ISMTransform, true);
			FVector WorldLocation = ISMTransform.GetLocation() + RelativeLocation;
			RelativeTransform.SetLocation(WorldLocation);
			
			return RelativeTransform;
		}

		RelativeLocation.Z = ISMTransform.GetLocation().Z + SocketTransform.GetLocation().Z;
		RelativeTransform.SetLocation(RelativeLocation);

		return RelativeTransform;
	}
	
	f_Success = false;
	return FTransform();
}

int ACS_BuildBaseComponent::GetHitISMComponentIndex(const FHitResult f_HitResult)
{
	//this function is currently being used. Leaving here to finish tutorial
	return f_HitResult.Item;
}


FTransform ACS_BuildBaseComponent::GetHitSocketTransform(const FHitResult& f_HitResult, float f_ValidHitDistance)
{
	const int HitIndex = f_HitResult.Item;
	FTransform ClosestSocket = FTransform();
	if(HitIndex != -1)
	{
		float ClosestDistance = f_ValidHitDistance;
		TArray<FName> SocketNamesArray = CircuitBoardInstancedMesh->GetAllSocketNames();
		for (const FName& SocketName : SocketNamesArray)
		{
			FTransform SocketTransform = CircuitBoardInstancedMesh->GetSocketTransform(SocketName);
			if(FVector::Distance(SocketTransform.GetLocation(), f_HitResult.Location) < ClosestDistance)
			{
				ClosestDistance = FVector::Distance(SocketTransform.GetLocation(), f_HitResult.Location);
				ClosestSocket = SocketTransform;
			}
		}
	}
	return ClosestSocket;
}

void ACS_BuildBaseComponent::AddInstanceToActor(const FTransform& f_ActorTransform, ECircuitComponentType f_CircuitCompType)
{
	switch (f_CircuitCompType)
	{
	case ECircuitComponentType::Base : CircuitBoardInstancedMesh->AddInstance(f_ActorTransform, true); break;
	case ECircuitComponentType::SocketBlock : CircuitBoardInstancedMesh->AddInstance(f_ActorTransform, true); break;
	case ECircuitComponentType::Jumper : CircuitBoardInstancedMesh->AddInstance(f_ActorTransform, true); break;
	case ECircuitComponentType::Receiver : CircuitBoardInstancedMesh->AddInstance(f_ActorTransform, true); break;
	case ECircuitComponentType::Laser : CircuitBoardInstancedMesh->AddInstance(f_ActorTransform, true); break;
	case ECircuitComponentType::Switch : CircuitBoardInstancedMesh->AddInstance(f_ActorTransform, true); break;	
	default : break;
	}
}
