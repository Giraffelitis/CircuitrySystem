// Copyright 2023 by Pace Abbott. All Rights Reserved.


#include "LaserSystem/CS_ReflectiveCube.h"
#include "Components/CS_TaggingSystem.h"

// Sets default values
ACS_ReflectiveCube::ACS_ReflectiveCube()
{
	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>("Base Mesh");
	RootComponent = BaseMesh;

	TaggingSystemComp = CreateDefaultSubobject<UCS_TaggingSystem>("TaggingSystemComp");
}

void ACS_ReflectiveCube::BeginPlay()
{
	Super::BeginPlay();

	BaseMesh->SetSimulatePhysics(true);	
	BaseMesh->SetMassOverrideInKg(NAME_None, 500.0f, true);
}

bool ACS_ReflectiveCube::IsReflective()
{
	return true;
}
