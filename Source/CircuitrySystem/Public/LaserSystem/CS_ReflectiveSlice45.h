// Copyright 2023 by Pace Abbott. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CS_ReflectiveSlice45.generated.h"

class UCS_TaggingSystem;

UCLASS()
class CIRCUITRYSYSTEM_API ACS_ReflectiveSlice45 : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACS_ReflectiveSlice45();

	virtual void BeginPlay() override;

	virtual bool IsReflective();

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* BaseMesh;

	UPROPERTY()
	UCS_TaggingSystem* TaggingSystemComp;

};
