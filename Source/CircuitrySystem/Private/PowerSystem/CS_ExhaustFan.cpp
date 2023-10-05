// Copyright 2023 by Pace Abbott. All Rights Reserved.


#include "PowerSystem/CS_ExhaustFan.h"

#include "Components/CS_AttachPoint.h"
#include "Components/CS_TaggingSystem.h"
#include "PowerSystem/CS_PowerComponent.h"
#include "Core/CS_NativeGameplayTagLibrary.h"

using namespace CS_NativeGameplayTagLibrary;

// Sets default values
ACS_ExhaustFan::ACS_ExhaustFan()
{
	FanHousing = CreateDefaultSubobject<UStaticMeshComponent>("LeftDoorPanel");
	FanHousing->SetupAttachment(BaseMesh);
	FanBlade = CreateDefaultSubobject<UStaticMeshComponent>("RightDoorPanel");
	FanBlade->SetupAttachment(BaseMesh);
	PowerSocket = CreateDefaultSubobject<UStaticMeshComponent>("PowerSocket");
	PowerSocket->SetupAttachment(BaseMesh);
	AttachPoint_0->SetupAttachment(PowerSocket);

	PowerComp->bIsPowered = false;
}

// Called when the game starts or when spawned
void ACS_ExhaustFan::BeginPlay()
{
	Super::BeginPlay();
	
	TaggingSystemComp->ActiveGameplayTags.AddTag(ItemTag_Power_Receiver);	
}

void ACS_ExhaustFan::UpdatePowerState()
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

void ACS_ExhaustFan::IsPowered_Implementation(AActor* f_Actor)
{
	Super::IsPowered_Implementation(f_Actor);
	
	PowerComp->ReceivingPowerFromArray.AddUnique(f_Actor);
	UpdatePowerState();
	StartFanTimer();
}

void ACS_ExhaustFan::IsNotPowered_Implementation(AActor* f_Actor)
{
	Super::IsNotPowered_Implementation(f_Actor);
	
	PowerComp->ReceivingPowerFromArray.Remove(f_Actor);
	UpdatePowerState();	
}

void ACS_ExhaustFan::StartFanTimer()
{
	GetWorld()->GetTimerManager().SetTimer(FanTimerHandle, this, &ACS_ExhaustFan::SpinFan, 0.001f, true);
}

void ACS_ExhaustFan::SpinFan()
{
	if(PowerComp->bIsPowered)
	{
		FanBlade->SetRelativeRotation(FanBlade->GetRelativeRotation() += FRotator(0.0f, 0.0f, 0.5f));
	}
	else
	{
		GetWorld()->GetTimerManager().ClearTimer(FanTimerHandle);
	}
}
