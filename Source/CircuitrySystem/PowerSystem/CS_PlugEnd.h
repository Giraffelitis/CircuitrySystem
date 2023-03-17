// Copyright 2023 by Pace Abbott. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "CS_AttachableActor.h"
#include "CS_PlugEnd.generated.h"

class UCS_TaggingSystem;
class UCS_PowerComponent;
UCLASS()
class CIRCUITRYSYSTEM_API ACS_PlugEnd : public ACS_AttachableActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ACS_PlugEnd();

	virtual void BeginPlay() override;
	virtual void Destroyed() override;
	virtual void IsPowered_Implementation(AActor* f_Actor) override;
	virtual void IsNotPowered_Implementation(AActor* f_Actor) override;
	virtual void CheckPoweredState_Implementation() override;
	void UpdateAttachedPowerState();

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* BaseMesh;
};
