// Copyright 2023 by Pace Abbott. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CS_DataTypes.h"
#include "CS_BuildHelperMesh.generated.h"

class ACS_CircuitComponentBase;
class UMaterialInstance;

UCLASS()
class CIRCUITRYSYSTEM_API ACS_BuildHelperMesh : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ACS_BuildHelperMesh();

	void SetBuildPosition(const FHitResult& f_HitResult);
	
	void SpawnBuildingComponent();
	
	UFUNCTION(BlueprintCallable, Category = "Build")
	void SetMeshArrayIndex(int f_Index);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Build")
	UStaticMeshComponent* CircuitMesh;
	
	UPROPERTY(EditDefaultsOnly, Category = "Build")
	TSubclassOf<ACS_CircuitComponentBase> CircuitComponentClass;

	UPROPERTY(EditDefaultsOnly, Category = "Build")
	TArray<FCircuitComponents> CircuitComponentsArray;
	int CircuitMeshIndex;

	UPROPERTY(EditDefaultsOnly, Category = "Build")
	UMaterialInstance* MaterialValid;
	UPROPERTY(EditDefaultsOnly, Category = "Build")
	UMaterialInstance* MaterialInvalid;

	bool bMaterialIsValid;
	bool bIsTargetingInstance;

	ACS_CircuitComponentBase* GetHitISMActor(const FHitResult& f_HitResult);

	void SetMeshToBase(const ECircuitComponentType& f_CircuitComponentType);
	void ReturnToPreviouslySelectedMesh();
	
	UPROPERTY()
	ACS_CircuitComponentBase* TargetedComponent;
};
