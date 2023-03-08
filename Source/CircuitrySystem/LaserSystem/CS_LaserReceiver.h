// Copyright 2023 by Pace Abbott. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "CircuitrySystem/PowerSystem/CS_PoweredInterface.h"
#include "GameFramework/Actor.h"
#include "CS_LaserReceiver.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FIsReceivingPower);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FLostPower);

class ACS_LaserBeam;
class UCS_TaggingSystem;

UCLASS()
class CIRCUITRYSYSTEM_API ACS_LaserReceiver : public AActor, public ICS_PoweredInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACS_LaserReceiver();

	/** Delegate to whom anyone can subscribe to receive this event */
	UPROPERTY(BlueprintAssignable, Category = "Power")
	FIsReceivingPower IsReceivingPower;

	UPROPERTY(BlueprintAssignable, Category = "Power")
	FIsReceivingPower LostPower;
	
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* BaseMesh;
	
	UPROPERTY()
	bool bIsPowered;

	UPROPERTY()
	UCS_TaggingSystem* TaggingSystemComp;
	
protected:

	virtual void IsPowered_Implementation() override;

	virtual void IsNotPowered_Implementation() override;

private:
	
	UPROPERTY()
	USceneComponent* SceneComp;

};
