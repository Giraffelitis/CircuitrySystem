// Copyright 2023 by Pace Abbott. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/StaticMeshActor.h"
#include "CS_LaserBeam.generated.h"

class UCS_TaggingSystem;
/**
 * 
 */
UCLASS()
class CIRCUITRYSYSTEM_API ACS_LaserBeam : public AStaticMeshActor
{
	GENERATED_BODY()

	ACS_LaserBeam();

	void SetLaserBeamTransform(FTransform f_NewTransform);

	UPROPERTY()
	UStaticMesh* BaseMesh;

	UPROPERTY()
	UCS_TaggingSystem* TaggingSystemComp;
	
};
