// Copyright 2023 by Pace Abbott. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CS_BuildCircuitBase.generated.h"

UCLASS()
class CIRCUITRYSYSTEM_API ACS_BuildCircuitBase : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ACS_BuildCircuitBase();

	TArray<FName> InstanceSocketsArray;

};
