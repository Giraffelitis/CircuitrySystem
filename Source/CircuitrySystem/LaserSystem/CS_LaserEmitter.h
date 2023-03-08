// Copyright 2023 by Pace Abbott. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CS_LaserEmitter.generated.h"

class ACS_LaserBeam;
class UArrowComponent;
class UCS_PowerComponent;
class UCS_TaggingSystem;

UCLASS()
class ACS_LaserEmitter : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACS_LaserEmitter();

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* BaseMesh;

	UPROPERTY()
	UCS_TaggingSystem* TaggingSystemComp;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	ACS_LaserBeam* SpawnBeam();
	
	void ShowBeam(int f_ArrayIndex, float f_BeamLength, float f_TotalBeamLength, FVector f_TraceStart, FVector f_TraceEnd);
	
	void HideBeam(int f_ArrayIndex);

	void StartLaserTrace(FVector &f_TraceStart, FVector &f_TraceEnd, FCollisionQueryParams f_QueryParams, TArray<FHitResult> &f_OutHitArray, TArray<FHitResult> &f_PreviousHitArray, float &f_TotalBeamLength, bool &f_bDoesLaserBounce, int f_Index);

	void CheckForLostActors(TArray<FHitResult> f_PreviousHitArray, TArray<FHitResult> f_OutHitArray);

	virtual void Destroyed() override;
	
	UPROPERTY(EditAnywhere)
	UArrowComponent* Arrow;

	UPROPERTY(EditDefaultsOnly, Category = "Trace")
	TEnumAsByte<ECollisionChannel> CollisionChannel;

	UPROPERTY()
	TArray<ACS_LaserBeam*> BeamArray;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<ACS_LaserBeam> LaserBeamClass;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UPhysicalMaterial> PoweredPhysMaterial;


	UPROPERTY(EditAnywhere)
	int MaxDeflections;

	UPROPERTY(EditAnywhere)
	float MaxLaserDistance;
	
private:
	FCollisionObjectQueryParams ObjectQueryParams;
	float DistanceTraveled;	
	FTransform BeamTransform;
	TArray<FHitResult> PreviousHitArray;
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	void GenerateLaser();
	
};
