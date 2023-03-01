// Copyright 2023 by Pace Abbott. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/SphereComponent.h"
#include "GameFramework/Actor.h"
#include "CS_LaserReceiver.generated.h"

class UCS_PowerComponent;
class ACS_LaserBeam;

UCLASS()
class CIRCUITRYSYSTEM_API ACS_LaserReceiver : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACS_LaserReceiver();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* BaseMesh;

	UPROPERTY(VisibleAnywhere)
	USphereComponent* SphereComponent;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	UPROPERTY(VisibleAnywhere)
	UCS_PowerComponent* PowerComp;

	UPROPERTY()
	bool bIsPowered;

private:
	TSubclassOf<ACS_LaserBeam> LaserBeamClass;

	UPROPERTY()
	TArray<AActor*> OverlappingActors;
	
};
