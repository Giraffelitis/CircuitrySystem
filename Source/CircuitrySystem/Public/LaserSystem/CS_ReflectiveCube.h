// Copyright 2023 by Pace Abbott. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CS_ReflectiveCube.generated.h"

class UCS_TaggingSystem;

UCLASS()
class CIRCUITRYSYSTEM_API ACS_ReflectiveCube : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACS_ReflectiveCube();

	virtual void BeginPlay() override;

	virtual bool IsReflective();

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* BaseMesh;

	UPROPERTY()
	UCS_TaggingSystem* TaggingSystemComp;
};