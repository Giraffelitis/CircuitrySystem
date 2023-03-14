// Copyright 2023 by Pace Abbott. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "CircuitrySystem/PowerSystem/CS_PoweredInterface.h"
#include "GameFramework/Actor.h"
#include "CS_LaserReceiver.generated.h"


class UCS_PowerComponent;
class UCS_TaggingSystem;

UCLASS()
class CIRCUITRYSYSTEM_API ACS_LaserReceiver : public AActor, public ICS_PoweredInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACS_LaserReceiver();


	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* BaseMesh;
	UPROPERTY(EditAnywhere)
	UCS_PowerComponent* PowerComp;
	UPROPERTY()
	UCS_TaggingSystem* TaggingSystemComp;
	
protected:

	virtual void IsPowered_Implementation() override;
	virtual void IsNotPowered_Implementation() override;

private:
	
	UPROPERTY()
	USceneComponent* SceneComp;

};
