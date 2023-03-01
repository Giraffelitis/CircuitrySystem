// Copyright 2023 by Pace Abbott. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CS_LaserEmitter.generated.h"

class ACS_LaserBeam;
class UArrowComponent;
class UCS_PowerComponent;

UCLASS()
class ACS_LaserEmitter : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACS_LaserEmitter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	ACS_LaserBeam* SpawnBeam();
	
	void ShowBeam(int ArrayIndex, FTransform NewTransform);
	
	void HideBeam(int ArrayIndex);

	bool StartLaserTrace(FVector &TraceStart, FVector &TraceEnd, FCollisionQueryParams QueryParams, TArray<FHitResult> &OutHitArray, float &TotalBeamLength, int Index);

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* BaseMesh;

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* RightSupport;

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* LeftSupport;

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* Cylinder;

	UPROPERTY(EditAnywhere)
	UArrowComponent* Arrow;

	UPROPERTY(EditDefaultsOnly, Category = "Trace")
	TEnumAsByte<ECollisionChannel> CollisionChannel;

	UPROPERTY()
	TArray<ACS_LaserBeam*> BeamArray;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<ACS_LaserBeam> LaserBeamClass;
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UCS_PowerComponent> PowerComponentClass;

	UPROPERTY(EditAnywhere)
	int MaxDeflections;

	UPROPERTY(EditAnywhere)
	float MaxLaserDistance;
	
private:
	FColor LineColor;
	FCollisionObjectQueryParams ObjectQueryParams;
	float DistanceTraveled;	
	FTransform BeamTransform;
	FVector LaserDefaultLocation;
	FRotator LaserDefaultRotation;
	FVector LaserDefaultScale;
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	void GenerateLaser();
	
};
