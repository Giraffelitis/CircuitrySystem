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

	PowerComp->bIsPowered = false;
	bDoorIsClosed = true;
	RightDoorPanelClosedLocation = FVector(0.0f ,172.0f, 0.0f);	
	LeftDoorPanelClosedLocation = FVector(0.0f ,328.0f, 0.0f);
	RightDoorPanelOpenLocation = FVector(0.0f ,112.0f, 0.0f);
	LeftDoorPanelOpenLocation = FVector(0.0f ,388.0f, 0.0f);
}

void ACS_Door::BeginPlay()
{
	Super::BeginPlay();
	TaggingSystemComp->ActiveGameplayTags.AddTag(ItemTag_Power_Receiver);
}

void ACS_Door::UpdatePowerState()
{
	if(PowerComp->ReceivingPowerFromArray.Num() > 0)
	{
		PowerComp->bIsPowered = true;
	}
	else
	{
		PowerComp->bIsPowered = false;
	}
}


void ACS_Door::IsPowered_Implementation(AActor* f_Actor)
{
	PowerComp->ReceivingPowerFromArray.AddUnique(f_Actor);
	UpdatePowerState();
	StartDoorMovementTimer();
}

void ACS_Door::IsNotPowered_Implementation(AActor* f_Actor)
{
	PowerComp->ReceivingPowerFromArray.Remove(f_Actor);
	UpdatePowerState();
	StartDoorMovementTimer();
}

//Start timer for AttachPoint checks
void ACS_Door::StartDoorMovementTimer()
{
	GetWorld()->GetTimerManager().SetTimer(DoorTimerHandle, this, &ACS_Door::AdjustDoorPanelPosition, 0.001f, true);
}

void ACS_Door::AdjustDoorPanelPosition()
{
	if(PowerComp->bIsPowered)
	{
		if(RightDoorPanel->GetRelativeLocation().Y >= RightDoorPanelOpenLocation.Y && LeftDoorPanel->GetRelativeLocation().Y <= LeftDoorPanelOpenLocation.Y)
		{
			RightDoorPanel->SetRelativeLocation(RightDoorPanel->GetRelativeLocation() + FVector(0.0f, -0.1f, 0.0f));
			LeftDoorPanel->SetRelativeLocation(LeftDoorPanel->GetRelativeLocation() + FVector(0.0f, 0.1f, 0.0f));
		}
		if(PowerComp->bIsPowered && RightDoorPanel->GetRelativeLocation().Y <= RightDoorPanelOpenLocation.Y && LeftDoorPanel->GetRelativeLocation().Y >= LeftDoorPanelOpenLocation.Y)
		{
			bDoorIsClosed = false;
			RightDoorPanel->SetRelativeLocation(RightDoorPanelOpenLocation);
			LeftDoorPanel->SetRelativeLocation(LeftDoorPanelOpenLocation);
			GetWorld()->GetTimerManager().ClearTimer(DoorTimerHandle);
		}
	}
	else if(!PowerComp->bIsPowered)
	{
		if (RightDoorPanel->GetRelativeLocation().Y <= RightDoorPanelClosedLocation.Y && LeftDoorPanel->GetRelativeLocation().Y >= LeftDoorPanelClosedLocation.Y)
		{
			RightDoorPanel->SetRelativeLocation(RightDoorPanel->GetRelativeLocation() + FVector(0.0f, 0.1f, 0.0f));
			LeftDoorPanel->SetRelativeLocation(LeftDoorPanel->GetRelativeLocation() + FVector(0.0f, -0.1f, 0.0f));
		}
		if(PowerComp->bIsPowered && RightDoorPanel->GetRelativeLocation().Y <= RightDoorPanelClosedLocation.Y && LeftDoorPanel->GetRelativeLocation().Y >= LeftDoorPanelClosedLocation.Y)
		{
			bDoorIsClosed = true;
			RightDoorPanel->SetRelativeLocation(RightDoorPanelClosedLocation);
			LeftDoorPanel->SetRelativeLocation(LeftDoorPanelClosedLocation);
			GetWorld()->GetTimerManager().ClearTimer(DoorTimerHandle);
		}
	}
}