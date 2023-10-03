// Copyright 2023 by Pace Abbott. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "PowerSystem/CS_PoweredInterface.h"
#include "GameFramework/Actor.h"
#include "CS_PowerableBase.generated.h"

class UBoxComponent;
class UCS_PowerComponent;
class UCS_TaggingSystem;
class UCS_AttachPoint;


UCLASS()
class CIRCUITRYSYSTEM_API ACS_PowerableBase : public AActor, public ICS_PoweredInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACS_PowerableBase();

	virtual void IsPowered_Implementation(AActor* f_Actor) override;
	virtual void IsNotPowered_Implementation(AActor* f_Actor) override;
	virtual void CheckPoweredState_Implementation() override;
	UFUNCTION()
	void UpdateAttachedPowerState();
	
	UPROPERTY(EditAnywhere)
	UCS_PowerComponent* PowerComp;

protected:
	virtual void BeginPlay() override;	
	virtual void Destroyed() override;
	virtual void PostInitializeComponents() override;
	void BindtoAPDelegates(UCS_AttachPoint* f_AttachPoint);
	void UpdateAttachedState(bool f_bIsAttached, AActor* f_AttachActor);

	UPROPERTY()
	TArray<UCS_AttachPoint*> AttachPoints;
	
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* BaseMesh;
	UPROPERTY(EditAnywhere)
	UCS_AttachPoint* AttachPoint_0;
	UPROPERTY(VisibleAnywhere)
	UCS_TaggingSystem* TaggingSystemComp;	

};
