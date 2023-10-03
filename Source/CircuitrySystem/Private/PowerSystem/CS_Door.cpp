// Copyright 2023 by Pace Abbott. All Rights Reserved.


#include "PowerSystem/CS_Door.h"

#include "Components/CS_AttachPoint.h"
#include "Components/CS_TaggingSystem.h"
#include "PowerSystem/CS_PowerComponent.h"
#include "Core/CS_NativeGameplayTagLibrary.h"

using namespace CS_NativeGameplayTagLibrary;

// Sets default values
ACS_Door::ACS_Door()
{
	LeftDoorPanel = CreateDefaultSubobject<UStaticMeshComponent>("LeftDoorPanel");
	LeftDoorPanel->SetupAttachment(BaseMesh);
	RightDoorPanel = CreateDefaultSubobject<UStaticMeshComponent>("RightDoorPanel");
	RightDoorPanel->SetupAttachment(BaseMesh);
	PowerSocket = CreateDefaultSubobject<UStaticMeshComponent>("PowerSocket");
	PowerSocket->SetupAttachment(BaseMesh);
	AttachPoint_0->SetupAttachment(PowerSocket);
}

void ACS_Door::BeginPlay()
{
	Super::BeginPlay();
	TaggingSystemComp->ActiveGameplayTags.AddTag(ItemTag_Power_Receiver);
}

void ACS_Door::IsPowered_Implementation(AActor* f_Actor)
{
	PowerComp->ReceivingPowerFromArray.AddUnique(f_Actor);
	UpdateAttachedPowerState();	
}

void ACS_Door::IsNotPowered_Implementation(AActor* f_Actor)
{
	PowerComp->ReceivingPowerFromArray.Remove(f_Actor);
	UpdateAttachedPowerState();
}



