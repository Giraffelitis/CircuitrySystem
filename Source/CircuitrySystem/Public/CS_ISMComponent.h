// Copyright 2023 by Pace Abbott. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/InstancedStaticMeshComponent.h"
#include "CS_ISMComponent.generated.h"

class UCS_TaggingSystem;
/**
 * 
 */
UCLASS()
class CIRCUITRYSYSTEM_API UCS_ISMComponent : public UInstancedStaticMeshComponent
{
	GENERATED_BODY()

	UCS_ISMComponent();

public:
	UPROPERTY()
	UCS_TaggingSystem* TaggingSystem;
	
};
