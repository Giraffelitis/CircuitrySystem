// Copyright 2023 by Pace Abbott. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "CS_ReflectiveInterface.h"
#include "GameFramework/Actor.h"
#include "CS_ReflectiveSlice45.generated.h"

UCLASS()
class CIRCUITRYSYSTEM_API ACS_ReflectiveSlice45 : public AActor, public ICS_ReflectiveInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACS_ReflectiveSlice45();

	virtual bool IsReflective();

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* BaseMesh;

};
