// Copyright 2023 by Pace Abbott. All Rights Reserved.


#include "CS_BuildHelperMesh.h"
#include "CS_BuildBaseComponent.h"
#include "Macros.h"


// Sets default values
ACS_BuildHelperMesh::ACS_BuildHelperMesh()
{
	PrimaryActorTick.bCanEverTick = false;

	BuildMesh = CreateDefaultSubobject<UStaticMeshComponent>("BuildMeshComponent");
	RootComponent = BuildMesh;

	CircuitMeshIndex = 0;

	bMaterialIsValid = false;
}

// Called when the game starts or when spawned
void ACS_BuildHelperMesh::BeginPlay()
{
	Super::BeginPlay();

	SetActorHiddenInGame(true);
	//Set mesh to display 
	if(CircuitComponentsArray[CircuitMeshIndex].CircuitMesh)
	{
		BuildMesh->SetStaticMesh(CircuitComponentsArray[CircuitMeshIndex].CircuitMesh);
	}
}

ACS_BuildBaseComponent* ACS_BuildHelperMesh::GetHitISMActor(const FHitResult& f_HitResult)
{
	return Cast<ACS_BuildBaseComponent>(f_HitResult.GetActor());
}

/** Shows placement of build component in game **/
void ACS_BuildHelperMesh::SetBuildPosition(const FHitResult& f_HitResult)
{
	if(f_HitResult.bBlockingHit)
	{
		SetActorHiddenInGame(false);
		TargetedComponent = GetHitISMActor(f_HitResult);
		if(TargetedComponent)
		{
			FTransform SocketTransform = TargetedComponent->GetHitSocketTransform(f_HitResult);
			if(!SocketTransform.Equals(FTransform()))
			{
				SetActorTransform(SocketTransform);
				if(MaterialValid && !bMaterialIsValid)
				{
					bMaterialIsValid = true;
					BuildMesh->SetMaterial(0,MaterialValid);
				}
			}
		}
		else
		{
			if(MaterialInvalid && bMaterialIsValid)
			{
				bMaterialIsValid = false;
				BuildMesh->SetMaterial(0,MaterialInvalid);
			}
			SetActorLocation(f_HitResult.Location);
		}
	}
	else
	{
		TargetedComponent = nullptr;
		SetActorHiddenInGame(true);
	}
}

/** Spawn selected mesh in world at selected location**/
void ACS_BuildHelperMesh::SpawnBuildingComponent()
{
	if(BuildingClass && !IsHidden())
	{
		if(TargetedComponent && bMaterialIsValid)
		{
			TargetedComponent->AddInstanceToActor(GetActorTransform(),CircuitComponentsArray[CircuitMeshIndex].CircuitComponentType );
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("SpawnActor"))
			GetWorld()->SpawnActor<ACS_BuildBaseComponent>(BuildingClass, GetActorTransform());
		}
	}
}

/** Set Mesh Array Index and update the mesh**/
void ACS_BuildHelperMesh::SetMeshArrayIndex(int f_Index)
{
	if(CircuitMeshIndex == 0 && f_Index == -1)
	{
		CircuitMeshIndex = CircuitComponentsArray.Num() - 1;
	}
	else if((CircuitMeshIndex + f_Index) >= CircuitComponentsArray.Num())
	{
		CircuitMeshIndex = 0;
	}
	else
	{
		CircuitMeshIndex += f_Index;
	}	
		
	if(CircuitComponentsArray.Num())
	BuildMesh->SetStaticMesh(CircuitComponentsArray[CircuitMeshIndex].CircuitMesh);	
}

