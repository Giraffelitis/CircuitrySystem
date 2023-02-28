// Copyright 2023 by Pace Abbott. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/StaticMeshActor.h"
#include "CS_LaserBeam.generated.h"

/**
 * 
 */
UCLASS()
class CIRCUITRYSYSTEM_API ACS_LaserBeam : public AStaticMeshActor
{
	GENERATED_BODY()

	ACS_LaserBeam();

	void SetLaserBeamTransform(FTransform NewTransform);

	UPROPERTY()
	UStaticMesh* BaseMesh;
	
};
