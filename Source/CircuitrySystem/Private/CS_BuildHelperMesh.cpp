// Copyright 2023 by Pace Abbott. All Rights Reserved.


#include "CS_BuildHelperMesh.h"
#include "CS_BuildCircuitISM.h"
#include "CS_ISMComponent.h"
#include "CS_TaggingSystem.h"
#include "GameplayTagContainer.h"
#include "Macros.h"
#include "CircuitrySystem/LaserSystem/CS_LaserEmitter.h"
#include "CircuitrySystem/LaserSystem/CS_LaserReceiver.h"
#include "CircuitrySystem/PowerSystem/CS_PowerBlock.h"
#include "CircuitrySystem/PowerSystem/CS_PowerCable.h"
#include "Components/InstancedStaticMeshComponent.h"
#include "Engine/StaticMeshSocket.h"
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

ACS_BuildCircuitISM* ACS_BuildHelperMesh::GetHitISMActor(const FHitResult& f_HitResult)
{
	return Cast<ACS_BuildCircuitISM>(f_HitResult.GetActor());
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
		
		CurrentHitSocket = FName(NAME_None);
		CurrentHitMesh = nullptr;
		CurrentHitActor = nullptr;
		
		if(TargetedComponent)
		{
			FTransform SocketTransform = TargetedComponent->GetHitInstanceSocketTransform(f_HitResult, CircuitComponentsArray[CircuitMeshIndex].FilterCharacter);
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
				{
					SetComponentGhostMaterial(true);
				}
			}
			else
			{
				SetComponentGhostMaterial(false);
				SetActorLocation(f_HitResult.Location);
			}
		}
		else
		{
			FTransform SocketTransform = GetHitActorSocketTransform(f_HitResult, CircuitComponentsArray[CircuitMeshIndex].FilterCharacter);
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
				{
					SetComponentGhostMaterial(true);
				}				
			}
			else
			{
				SetComponentGhostMaterial(false);
				if(CircuitComponentsArray[CircuitMeshIndex].CircuitComponentType == ECircuitComponentType::Base)
				{
					if(CheckOverlappedActors())
					{
						SetComponentGhostMaterial(true);
					}
				}
				SetActorLocation(f_HitResult.Location);
				SetActorRotation(CompGhostRot);
			}
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
		if(!IsValid(OverlappedActor)) continue;
		
		UActorComponent* ActorComp = OverlappedActor->GetComponentByClass(UCS_TaggingSystem::StaticClass());
		if(!IsValid(ActorComp)) continue;
			
		UCS_TaggingSystem* TagSystemComp = Cast<UCS_TaggingSystem>(ActorComp);
		if(!IsValid(TagSystemComp)) continue;
		
		if(TagSystemComp->BlockingTags.HasAnyExact(CurrentIDTags))
			return false;		
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
		if(!IsValid(ISMComp)) continue;
		
		if(ISMComp->TaggingSystem->BlockingTags.HasAnyExact(CurrentIDTags))
			return false;
		
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
				if(CircuitComponentsArray[CircuitMeshIndex].bIsActor)
				{
					AddActorToActor(GetActorTransform(),CircuitComponentsArray[CircuitMeshIndex].CircuitComponentType, CurrentBlockingTags);
				}
				if(IsValid(TargetedComponent))
				{
					TargetedComponent->AddInstanceToActor(GetActorTransform(),CircuitComponentsArray[CircuitMeshIndex].CircuitComponentType, CurrentBlockingTags);
				}
			}
		}		
		else
		{
			if(bMaterialIsValid)
			{
				if(CircuitComponentsArray[CircuitMeshIndex].CircuitComponentType == ECircuitComponentType::Base)
				{
					ACS_BuildCircuitISM* CircuitBase = GetWorld()->SpawnActor<ACS_BuildCircuitISM>(CircuitComponentClass, GetActorTransform());
					CircuitBase->TaggingSystemComp->ActiveGameplayTags.AddTag(FGameplayTag::RequestGameplayTag("BuildTag.Player"));
					CircuitBase->TaggingSystemComp->BlockingTags.AppendTags(CurrentBlockingTags);
				}
				if(CircuitComponentsArray[CircuitMeshIndex].bIsActor)
				{					
					AddActorToActor(GetActorTransform(),CircuitComponentsArray[CircuitMeshIndex].CircuitComponentType, CurrentBlockingTags);
					
				}
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

void ACS_BuildHelperMesh::GenerateSocketArray()
{
	ACS_PowerBlock* TempPower = GetWorld()->SpawnActor<ACS_PowerBlock>(PowerBlock);
	BuildCircuitBase->InstanceSocketsArray.Append(TempPower->SocketsArray);
	TempPower->Destroy();	
}

void ACS_BuildHelperMesh::DestroyActor(const FHitResult f_HitResult)
{
	if(f_HitResult.GetActor())
		DestroyActor(f_HitResult);
}

FTransform ACS_BuildHelperMesh::GetHitActorSocketTransform(const FHitResult& f_HitResult, const FName& f_Filter, float f_ValidHitDistance)
{
	if(AActor* HitActor = Cast<AActor>(f_HitResult.GetActor()))
	{
		CurrentHitActor = HitActor;
		FTransform ClosestSocket = FTransform();	
		float ClosestDistance = f_ValidHitDistance;
		TArray<UStaticMeshComponent*> Meshes;
		HitActor->GetComponents<UStaticMeshComponent>(Meshes);
		for(UStaticMeshComponent* Mesh : Meshes)
		{
			TArray<FName>SocketNames = Mesh->GetAllSocketNames();
			for (FName SocketName : SocketNames)
			{
				if(IsValidSocket(f_HitResult, f_Filter, SocketName))
				{
					FTransform SocketTransform = Mesh->GetSocketTransform(SocketName, RTS_World);
					if(FVector::Distance(SocketTransform.GetLocation(), f_HitResult.ImpactPoint) < ClosestDistance)
					{
						ClosestDistance = FVector::Distance(SocketTransform.GetLocation(), f_HitResult.ImpactPoint);
						ClosestSocket = SocketTransform;
						CurrentHitMesh = Mesh;
						CurrentHitSocket = SocketName;
					}
				}
			}
		}
		return ClosestSocket;
	}
	return FTransform();
}

bool ACS_BuildHelperMesh::IsValidSocket(const FHitResult& f_HitResult, const FName& f_Filter, const FName& f_SocketName)
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

void ACS_BuildHelperMesh::AddActorToActor(const FTransform& f_ActorTransform, ECircuitComponentType f_CircuitCompType, FGameplayTagContainer& f_BlockingTags)
{
	switch (f_CircuitCompType)
	{
	case ECircuitComponentType::PowerCable :
		{
			ACS_PowerCable* m_PowerCable = GetWorld()->SpawnActor<ACS_PowerCable>(PowerCable);
			if(IsValid(CurrentHitMesh))
			{
				CurrentHitMesh->GetSocketByName(CurrentHitSocket)->AttachActor(m_PowerCable, CurrentHitMesh);
			}
			else
			{
				m_PowerCable->SetActorTransform(f_ActorTransform);
			}
			CheckPoweredActors();
		//	m_PowerCable->TaggingSystemComp->ActiveGameplayTags.AddTag(FGameplayTag::RequestGameplayTag("BuildTag.Player"));
			break;
		}
	case ECircuitComponentType::Laser :
		{
			ACS_LaserEmitter* m_Emitter = GetWorld()->SpawnActor<ACS_LaserEmitter>(LaserEmitter);
			if(IsValid(CurrentHitMesh))
			{
				CurrentHitMesh->GetSocketByName(CurrentHitSocket)->AttachActor(m_Emitter, CurrentHitMesh);
			}
			else
			{
				m_Emitter->SetActorTransform(f_ActorTransform);
			}
			CheckPoweredActors();
			m_Emitter->BaseMesh->SetMobility(EComponentMobility::Static);
			m_Emitter->TaggingSystemComp->ActiveGameplayTags.AddTag(FGameplayTag::RequestGameplayTag("BuildTag.Player"));
			break;
		}		
	case ECircuitComponentType::Receiver :
		{
			ACS_LaserReceiver* m_Receiver = GetWorld()->SpawnActor<ACS_LaserReceiver>(LaserReceiver);
			if(IsValid(CurrentHitMesh))
			{
				CurrentHitMesh->GetSocketByName(CurrentHitSocket)->AttachActor(m_Receiver, CurrentHitMesh);
				PRINTF(-1, 10.0f, FColor::Black, "%p Attached To  %p", m_Receiver, CurrentHitMesh);

				
			}
			else
			{
				m_Receiver->SetActorTransform(f_ActorTransform);
			}
			CheckPoweredActors();
			m_Receiver->TaggingSystemComp->ActiveGameplayTags.AddTag(FGameplayTag::RequestGameplayTag("BuildTag.Player"));
			break;
		}	
	case ECircuitComponentType::PowerBlock :
		{			
			ACS_PowerBlock* m_PowerBlock = GetWorld()->SpawnActor<ACS_PowerBlock>(PowerBlock);
			if(IsValid(CurrentHitMesh))
			{
				CurrentHitMesh->GetSocketByName(CurrentHitSocket)->AttachActor(m_PowerBlock, CurrentHitMesh);
			}
			else
			{
				m_PowerBlock->SetActorTransform(f_ActorTransform);
			}
			CheckPoweredActors();
			m_PowerBlock->TaggingSystemComp->ActiveGameplayTags.AddTag(FGameplayTag::RequestGameplayTag("BuildTag.Player"));
			m_PowerBlock->CheckPoweredState_Implementation();
			break;
		}
		
	case ECircuitComponentType::Switch : break;	
	default : break;
	}
}

void ACS_BuildHelperMesh::CheckPoweredActors()
{
	if(IsValid(CurrentHitActor))
	{
		if(CurrentHitActor->Implements<UCS_PoweredInterface>())
		{
			ICS_PoweredInterface::Execute_CheckPoweredState(CurrentHitActor);
		}
	}
}