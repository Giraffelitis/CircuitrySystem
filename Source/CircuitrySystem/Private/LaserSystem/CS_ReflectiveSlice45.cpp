// Copyright 2023 by Pace Abbott. All Rights Reserved.


#include "LaserSystem/CS_ReflectiveSlice45.h"

#include "Components/CS_TaggingSystem.h"

// Sets default values
ACS_ReflectiveSlice45::ACS_ReflectiveSlice45()
{
	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>("Base Mesh");
	RootComponent = BaseMesh;
	
	TaggingSystemComp = CreateDefaultSubobject<UCS_TaggingSystem>("TaggingSystemComp");
}

void ACS_ReflectiveSlice45::BeginPlay()
{
	Super::BeginPlay();	
	
	BaseMesh->SetSimulatePhysics(true);
	BaseMesh->SetMassOverrideInKg(NAME_None, 250.0f, true);
}

bool ACS_ReflectiveSlice45::IsReflective()
{
	return true;
}


