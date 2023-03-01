// Copyright 2023 by Pace Abbott. All Rights Reserved.


#include "CS_Light.h"
#include "Macros.h"
#include "CircuitrySystem/LaserSystem/CS_LaserReceiver.h"
#include "Engine/PointLight.h"

ACS_Light::ACS_Light()
{
	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>("BaseMesh");
	RootComponent = BaseMesh;
}

void ACS_Light::BeginPlay()
{
	LaserReceiver->AttachToActor(this, AttachRules->SnapToTargetNotIncludingScale, NAME_None);
	LaserReceiver->IsReceivingPower.AddDynamic(this, &ACS_Light::HasPower);
}

void ACS_Light::HasPower()
{	
	Light->SetLightColor(FLinearColor(0.0f, 255.0f, 0.0f,1.0f));

#if !UE_BUILD_SHIPPING
	PRINT(-1, 1.0f, FColor::Black, "Light Powered");
#endif
	
}
