// Copyright 2023 by Pace Abbott. All Rights Reserved.


#include "LaserSystem/CS_ReflectiveCube.h"
#include "Components/CS_TaggingSystem.h"

// Sets default values
ACS_ReflectiveCube::ACS_ReflectiveCube()
{
	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>("Base Mesh");
	RootComponent = BaseMesh;

	BaseMesh->SetSimulatePhysics(true);	
	BaseMesh->SetMassOverrideInKg(NAME_None, 500.0f, true);

	TaggingSystemComp = CreateDefaultSubobject<UCS_TaggingSystem>("TaggingSystemComp");
}

bool ACS_ReflectiveCube::IsReflective()
{
	return true;
}
