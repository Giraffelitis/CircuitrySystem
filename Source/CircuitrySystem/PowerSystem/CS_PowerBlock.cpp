// Copyright 2023 by Pace Abbott. All Rights Reserved.


#include "CS_PowerBlock.h"
#include "Macros.h"
#include "CircuitrySystem/LaserSystem/CS_LaserReceiver.h"
#include "Engine/PointLight.h"

ACS_PowerBlock::ACS_PowerBlock()
{
	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>("BaseMesh");
	RootComponent = BaseMesh;
}

void ACS_PowerBlock::BeginPlay()
{
	if(IsValid(LaserReceiver))
	{
		LaserReceiver->AttachToActor(this, AttachRules->SnapToTargetIncludingScale, FName(TEXT("Top_Socket")));
		LaserReceiver->BaseMesh->SetCollisionProfileName(FName(TEXT("Laser")));
		LaserReceiver->IsReceivingPower.AddDynamic(this, &ACS_PowerBlock::HasPower);
		LaserReceiver->LostPower.AddDynamic(this, &ACS_PowerBlock::LostPower);
	}
}

void ACS_PowerBlock::HasPower()
{
	for(const auto AffectedActor: ConnectedActorsArray)
	{
		PointLight = Cast<APointLight>(AffectedActor);
	
		PointLight->SetLightColor(FLinearColor(0.0f, 255.0f, 0.0f,1.0f));
	}
}

void ACS_PowerBlock::LostPower()
{
	for(const auto AffectedActor: ConnectedActorsArray)
	{
		PointLight = Cast<APointLight>(AffectedActor);
	
		PointLight->SetLightColor(FLinearColor(255.0f, 255.0f, 255.0f, 0.1f));
	}
}
