// Copyright 2023 by Pace Abbott. All Rights Reserved.


#include "CS_ReflectiveCube.h"

// Sets default values
ACS_ReflectiveCube::ACS_ReflectiveCube()
{
	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>("Base Mesh");
	RootComponent = BaseMesh;

	BaseMesh->SetSimulatePhysics(true);	
	BaseMesh->SetMassOverrideInKg(NAME_None, 500.0f, true);
}

bool ACS_ReflectiveCube::IsReflective()
{
	return true;
}