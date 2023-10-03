// Copyright 2023 by Pace Abbott. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Actors/CS_AttachableActor.h"
#include "CS_PoweredInterface.h"
#include "CS_PowerCable.generated.h"

class ACS_PlugEnd;
class UCableComponent;
class UCS_PowerComponent;
class UCS_TaggingSystem;
/**
 * 
 */
UCLASS()
class CIRCUITRYSYSTEM_API ACS_PowerCable : public ACS_AttachableActor
{
	GENERATED_BODY()

public:
	ACS_PowerCable();
	void SpawnPlugB();
	void UpdateAttachedPowerState();
	
protected:

	virtual void BeginPlay() override;
	virtual void Destroyed() override;

	void UpdatePlugPower();
	void UpdateAttachedToPower();
	void UpdateMesh();
	
	virtual void IsPowered_Implementation(AActor* f_Actor) override;
	virtual void IsNotPowered_Implementation(AActor* f_Actor) override;
	virtual void CheckPoweredState_Implementation() override;
	
	UPROPERTY(EditDefaultsOnly, Category = "Power")
	UStaticMeshComponent* PlugEnd_A;
	UPROPERTY()
	ACS_PlugEnd* PlugEnd_B;
	UPROPERTY(EditDefaultsOnly, Category = "Power")
	TSubclassOf<ACS_PlugEnd> PlugEnd_BClass;
	UPROPERTY(EditDefaultsOnly, Category = "Power")
	UCableComponent* CableComp;
	UPROPERTY()
	UMeshComponent* CableMesh;
	UPROPERTY(EditDefaultsOnly, Category = "Power")
	UMaterialInstance* MaterialPowered;
	UPROPERTY(EditDefaultsOnly, Category = "Power")
	UMaterialInstance* MaterialNotPowered;

};
