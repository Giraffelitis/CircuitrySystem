// Copyright 2023 by Pace Abbott. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "CS_ReflectiveInterface.h"
#include "GameFramework/Actor.h"
#include "CS_ReflectiveCube.generated.h"

UCLASS()
class CIRCUITRYSYSTEM_API ACS_ReflectiveCube : public AActor, public ICS_ReflectiveInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACS_ReflectiveCube();

	virtual bool IsReflective();

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* BaseMesh;
};
