// Copyright 2023 by Pace Abbott. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Core/CS_DataTypes.h"
#include "CS_BuildCircuitBase.h"
#include "CS_BuildCircuitISM.generated.h"

class UCS_ISMComponent;
class UCS_TaggingSystem;

UCLASS()
class CIRCUITRYSYSTEM_API ACS_BuildCircuitISM : public ACS_BuildCircuitBase
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACS_BuildCircuitISM();

	UPROPERTY(EditDefaultsOnly, Category = "Circuitry")
	UCS_ISMComponent* CircuitBoardInstancedMesh;
	UPROPERTY()
	TSubclassOf<ACS_BuildCircuitBase> BuildCircuitBaseClass;
	UPROPERTY()
	UCS_TaggingSystem* TaggingSystemComp;
	
	int TotalNumOfParts = 0;
	
	UFUNCTION(BlueprintCallable, Category = "Circuitry")
	void DestroyInstance(const FHitResult f_HitResult);

	int GetHitISMComponentIndex(const FHitResult f_HitResult);

	bool IsValidSocket(const FHitResult& f_HitResult, const FName& f_Filter, const FName& f_SocketName);
	
	FTransform GetHitInstanceSocketTransform(const FHitResult& f_HitResult, const FName& f_Filter, float f_ValidHitDistance = 200.0f);

	void AddInstanceToActor(const FTransform& f_ActorTransform, ECircuitComponentType f_CircuitCompType, FGameplayTagContainer& f_BlockingTags);

	UPROPERTY()
	ACS_BuildCircuitBase* BuildCircuitBase;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	void GenerateSocketArray();

	FTransform GetISMSocketTransform(UInstancedStaticMeshComponent* f_ISMComponent, int32 f_ISMIndex, const FName& f_SocketName);
};
