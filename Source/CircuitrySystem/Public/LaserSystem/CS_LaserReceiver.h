// Copyright 2023 by Pace Abbott. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Actors/CS_AttachableActor.h"
#include "CS_LaserReceiver.generated.h"


class UCS_PowerComponent;
class UCS_TaggingSystem;

UCLASS()
class CIRCUITRYSYSTEM_API ACS_LaserReceiver : public ACS_AttachableActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACS_LaserReceiver();


	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* BaseMesh;
	
protected:

	virtual void BeginPlay() override;
	virtual void IsPowered_Implementation(AActor* f_Actor) override;
	virtual void IsNotPowered_Implementation(AActor* f_Actor) override;
	void UpdateAttachedPowerState();

private:
	
	UPROPERTY()
	USceneComponent* SceneComp;

};
