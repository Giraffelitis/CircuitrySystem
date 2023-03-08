// Copyright 2023 by Pace Abbott. All Rights Reserved.


#include "CS_BuildHelperMesh.h"
#include "CS_CircuitComponentBase.h"
#include "CS_TaggingSystem.h"
#include "GameplayTagContainer.h"
#include "Macros.h"


// Sets default values
ACS_BuildHelperMesh::ACS_BuildHelperMesh()
{
	PrimaryActorTick.bCanEverTick = false;

	CircuitMesh = CreateDefaultSubobject<UStaticMeshComponent>("BuildMeshComponent");
	RootComponent = CircuitMesh;

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
		CircuitMesh->SetStaticMesh(CircuitComponentsArray[CircuitMeshIndex].CircuitMesh);
	}
}

ACS_CircuitComponentBase* ACS_BuildHelperMesh::GetHitISMActor(const FHitResult& f_HitResult)
{
	return Cast<ACS_CircuitComponentBase>(f_HitResult.GetActor());
}

void ACS_BuildHelperMesh::SetMeshToBase(const ECircuitComponentType& f_CircuitComponentType)
{
	bIsTargetingInstance = false;
	for (const FCircuitComponents& CircuitComp : CircuitComponentsArray)
	{
		if (CircuitComp.CircuitComponentType == f_CircuitComponentType)
		{
			CircuitMesh->SetStaticMesh(CircuitComp.CircuitMesh);
		}
	}
}

void ACS_BuildHelperMesh::ReturnToPreviouslySelectedMesh()
{
	bIsTargetingInstance = true;
	if(CircuitComponentsArray[CircuitMeshIndex].CircuitMesh)
	{
		CircuitMesh->SetStaticMesh(CircuitComponentsArray[CircuitMeshIndex].CircuitMesh);
	}	
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
			if(!bIsTargetingInstance)
			{
				ReturnToPreviouslySelectedMesh();
			}
			FTransform SocketTransform = TargetedComponent->GetHitSocketTransform(f_HitResult,CircuitComponentsArray[CircuitMeshIndex].FilterCharacter);
			if(!SocketTransform.Equals(FTransform()))
			{
				SetActorTransform(SocketTransform);
				if(MaterialValid && !bMaterialIsValid)
				{
					bMaterialIsValid = true;
					CircuitMesh->SetMaterial(0,MaterialValid);
				}
			}
			else
			{				
				if(MaterialInvalid && bMaterialIsValid)
				{
					bMaterialIsValid = false;
					CircuitMesh->SetMaterial(0,MaterialInvalid);
				}
				SetActorLocation(f_HitResult.Location);
			}
		}
		else
		{
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
	if(CircuitComponentClass && !IsHidden())
	{
		if(TargetedComponent)
		{
			if(bMaterialIsValid)
			{
				TargetedComponent->AddInstanceToActor(GetActorTransform(),CircuitComponentsArray[CircuitMeshIndex].CircuitComponentType);
			}
		}			
		else
		{
			ACS_CircuitComponentBase* CircuitBase = GetWorld()->SpawnActor<ACS_CircuitComponentBase>(CircuitComponentClass, GetActorTransform());
			CircuitBase->TaggingSystemComp->BaseTagContainer.AddTag(FGameplayTag::RequestGameplayTag("BuildTag.Player"));
		}
	}
}

/** Set Mesh Array Index and update the mesh**/
void ACS_BuildHelperMesh::SetMeshArrayIndex(int f_Index)
{
	if(bIsTargetingInstance)
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
			CircuitMesh->SetStaticMesh(CircuitComponentsArray[CircuitMeshIndex].CircuitMesh);
	}
}

