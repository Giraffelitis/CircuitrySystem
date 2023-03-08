// Copyright 2023 by Pace Abbott. All Rights Reserved.


#include "CS_ReflectiveSlice45.h"

#include "CS_TaggingSystem.h"

// Sets default values
ACS_ReflectiveSlice45::ACS_ReflectiveSlice45()
{
	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>("Base Mesh");
	RootComponent = BaseMesh;

	BaseMesh->SetSimulatePhysics(true);
	BaseMesh->SetMassOverrideInKg(NAME_None, 250.0f, true);

	TaggingSystemComp = CreateDefaultSubobject<UCS_TaggingSystem>("TaggingSystemComp");
}

bool ACS_ReflectiveSlice45::IsReflective()
{
	return true;
}


