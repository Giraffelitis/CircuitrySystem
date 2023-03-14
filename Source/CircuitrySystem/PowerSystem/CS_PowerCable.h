// Copyright 2023 by Pace Abbott. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "CableActor.h"
#include "CS_PowerCable.generated.h"

class UCS_PowerComponent;
/**
 * 
 */
UCLASS()
class CIRCUITRYSYSTEM_API ACS_PowerCable : public ACableActor
{
	GENERATED_BODY()

	ACS_PowerCable();
	
	UPROPERTY(EditAnywhere)
	UCS_PowerComponent* PowerComp;
};
