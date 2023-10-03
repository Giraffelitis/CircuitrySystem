// Copyright 2023 by Pace Abbott. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CS_PowerGeneratorBase.generated.h"

class UCS_PowerComponent;
/**
 * 
 */
UCLASS()
class ACS_PowerGeneratorBase : public AActor
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	UCS_PowerComponent* PowerComp;
};
