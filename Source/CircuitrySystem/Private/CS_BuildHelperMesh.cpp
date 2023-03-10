// Copyright 2023 by Pace Abbott. All Rights Reserved.


#include "CS_BuildHelperMesh.h"
#include "CS_CircuitComponentBase.h"
#include "CS_ISMComponent.h"
#include "CS_TaggingSystem.h"
#include "GameplayTagContainer.h"
#include "GeometryTypes.h"
#include "Macros.h"
#include "Components/InstancedStaticMeshComponent.h"
#include "Kismet/KismetMathLibrary.h"


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
		CurrentIDTags = CircuitComponentsArray[CircuitMeshIndex].MeshIDTags;
		CurrentBlockingTags = CircuitComponentsArray[CircuitMeshIndex].MeshBlockingTags;
	}
}

ACS_CircuitComponentBase* ACS_BuildHelperMesh::GetHitISMActor(const FHitResult& f_HitResult)
{
	return Cast<ACS_CircuitComponentBase>(f_HitResult.GetActor());
}

/** Shows placement of build component in game **/
void ACS_BuildHelperMesh::SetBuildPosition(const FHitResult& f_HitResult)
{
	if(f_HitResult.bBlockingHit)
	{
		//Show mesh on screen and create variable if hit object is part of a circuit
		SetActorHiddenInGame(false);
		TargetedComponent = GetHitISMActor(f_HitResult);
		
		if(!CheckOverlappedActors())
			SetComponentGhostMaterial(false);
		
		if(TargetedComponent)
		{
			FTransform SocketTransform = TargetedComponent->GetHitSocketTransform(f_HitResult,CircuitComponentsArray[CircuitMeshIndex].FilterCharacter);
			if(!SocketTransform.Equals(FTransform()))
			{
				//Checks if selected component is able to rotate on a socket
				if(CircuitComponentsArray[CircuitMeshIndex].bCanRotateOnSocket)
				{
					SetActorLocation(SocketTransform.GetLocation());
					SetActorRotation(FRotator(SocketTransform.GetRotation().Rotator().Pitch, CompGhostRot.Yaw, SocketTransform.GetRotation().Rotator().Roll));
				}
				else
				{
					SetActorTransform(SocketTransform);
				}
				
				if(CheckOverlappedActors())
					SetComponentGhostMaterial(true);				
			}
			else
			{
				SetComponentGhostMaterial(false);
				SetActorLocation(f_HitResult.Location);
			}
		}
		// If actor isn't hitting a circuit component
		else
		{
		
			SetComponentGhostMaterial(false);
			if(CircuitComponentsArray[CircuitMeshIndex].CircuitComponentType == ECircuitComponentType::Base)
			{
				if(CheckOverlappedActors())
					SetComponentGhostMaterial(true);
			}
			SetActorLocation(f_HitResult.Location);
			SetActorRotation(CompGhostRot);
		}
	}
	else
	{
		TargetedComponent = nullptr;
		SetActorHiddenInGame(true);
	}
}

void ACS_BuildHelperMesh::SetComponentGhostMaterial(bool f_bValidLocation)
{
	if(f_bValidLocation)
	{
		if(MaterialValid && !bMaterialIsValid)
		{
			bMaterialIsValid = true;
			CircuitMesh->SetMaterial(0,MaterialValid);
		}
	}
	else if(MaterialInvalid && bMaterialIsValid)
	{
		bMaterialIsValid = false;
		CircuitMesh->SetMaterial(0,MaterialInvalid);
		
	}
}

bool ACS_BuildHelperMesh::CheckOverlappedActors()
{
	TArray<AActor*> OverlappedActors;
	this->GetOverlappingActors(OverlappedActors);
	for (AActor* OverlappedActor : OverlappedActors)
	{
		UActorComponent* ActorComp = OverlappedActor->GetComponentByClass(UCS_TaggingSystem::StaticClass());
		if(IsValid(ActorComp))
		{
			UCS_TaggingSystem* TagSystemComp = Cast<UCS_TaggingSystem>(ActorComp);
			if(IsValid(TagSystemComp))
			{		
				if(TagSystemComp->BlockingTags.HasAnyExact(CurrentIDTags))
					return false;
			}
		}
	}
	return CheckOverlappedComponents();
}

bool ACS_BuildHelperMesh::CheckOverlappedComponents()
{
	TArray<UPrimitiveComponent*> OverlappedComponents;
	this->GetOverlappingComponents(OverlappedComponents);
	for(UPrimitiveComponent* OverlapComponent : OverlappedComponents)
	{
		UCS_ISMComponent* ISMComp =  Cast<UCS_ISMComponent>(OverlapComponent);
		if(IsValid(ISMComp))
		{
			if(ISMComp->TaggingSystem->BlockingTags.HasAnyExact(CurrentIDTags))
				return false;
		}
	}
	return true;
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
				TargetedComponent->AddInstanceToActor(GetActorTransform(),CircuitComponentsArray[CircuitMeshIndex].CircuitComponentType, CurrentBlockingTags);
			}
		}			
		else
		{
			if(bMaterialIsValid)
			{
				ACS_CircuitComponentBase* CircuitBase = GetWorld()->SpawnActor<ACS_CircuitComponentBase>(CircuitComponentClass, GetActorTransform());
				CircuitBase->TaggingSystemComp->ActiveGameplayTags.AddTag(FGameplayTag::RequestGameplayTag("BuildTag.Player"));
				CircuitBase->TaggingSystemComp->BlockingTags.AppendTags(CurrentBlockingTags);
			}
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
		CircuitMesh->SetStaticMesh(CircuitComponentsArray[CircuitMeshIndex].CircuitMesh);
		CurrentIDTags = CircuitComponentsArray[CircuitMeshIndex].MeshIDTags;
		CurrentBlockingTags = CircuitComponentsArray[CircuitMeshIndex].MeshBlockingTags;
}

