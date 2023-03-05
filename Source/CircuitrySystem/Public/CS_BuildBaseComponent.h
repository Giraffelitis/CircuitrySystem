// Copyright 2023 by Pace Abbott. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CS_DataTypes.h"
#include "CS_BuildBaseComponent.generated.h"

class UInstancedStaticMeshComponent;

UCLASS()
class CIRCUITRYSYSTEM_API ACS_BuildBaseComponent : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACS_BuildBaseComponent();

	UPROPERTY(EditDefaultsOnly, Category = "Circuitry")
	UInstancedStaticMeshComponent* CircuitBoardInstancedMesh;

	UPROPERTY(EditDefaultsOnly, Category = "Circuitry")
	UInstancedStaticMeshComponent* SocketBlockInstancedMesh;

	UFUNCTION(BlueprintCallable, Category = "Circuitry")
	void DestroyInstance(FVector f_HitPoint);

	int GetHitISMComponentIndex(const FHitResult f_HitResult);

	FTransform GetHitSocketTransform(const FHitResult& f_HitResult, float f_ValidHitDistance = 100.0f);

	void AddInstanceToActor(const FTransform& f_ActorTransform, ECircuitComponentType f_CircuitCompType);
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	FTransform GetISMSocketTransform(UInstancedStaticMeshComponent* f_ISMComponent, int32 f_ISMIndex, const FName& f_SocketName, bool& f_Success, bool f_WorldSpace);
};
