// Copyright 2023 by Pace Abbott. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CS_LaserEmitter.generated.h"

class UArrowComponent;

UCLASS()
class ACS_LaserEmitter : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACS_LaserEmitter();

	UPROPERTY(EditAnywhere)
	bool bDebugDraw;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

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

private:
	bool bBlockingHit;
	FHitResult HitActor;
	FColor LineColor;
	FVector StartLocation;
	FVector EndLocation;
	FCollisionObjectQueryParams ObjectQueryParams;
	float MaxLaserDistance;
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
