// Copyright 2023 by Pace Abbott. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CS_DataTypes.h"
#include "CS_BuildHelperMesh.generated.h"

struct FGameplayTagContainer;
struct FGameplayTag;
class ACS_BuildCircuitBase;
class ACS_BuildCircuitISM;
class ACS_PowerBlock;
class ACS_LaserEmitter;
class ACS_LaserReceiver;
class ACS_PowerCable;
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
	void GenerateSocketArray();
	void DestroyActor(FHitResult f_HitResult);
	bool IsValidSocket(const FHitResult& f_HitResult, const FName& f_Filter, const FName& f_SocketName);
	FTransform GetHitActorSocketTransform(const FHitResult& f_HitResult, const FName& f_Filter,
	                                      float f_ValidHitDistance = 200.0f);
	void AddActorToActor(const FTransform& f_ActorTransform, ECircuitComponentType f_CircuitCompType,
	                     FGameplayTagContainer& f_BlockingTags);

	FRotator CompGhostRot;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, Category = "Circuitry")
	TSubclassOf<ACS_PowerBlock> PowerBlock;
	UPROPERTY(EditDefaultsOnly, Category = "Circuitry")
	TSubclassOf<ACS_LaserEmitter> LaserEmitter;
	UPROPERTY(EditDefaultsOnly, Category = "Circuitry")
	TSubclassOf<ACS_LaserReceiver> LaserReceiver;
	UPROPERTY(EditDefaultsOnly, Category = "Circuitry")
	TSubclassOf<ACS_PowerCable> PowerCable;
	UPROPERTY(EditDefaultsOnly, Category = "Circuitry")
	TSubclassOf<ACS_BuildCircuitBase> BuildCircuitBaseClass;
	UPROPERTY()
	ACS_BuildCircuitBase* BuildCircuitBase;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Build")
	UStaticMeshComponent* CircuitMesh;
	UPROPERTY(EditDefaultsOnly, Category = "Build")
	TSubclassOf<ACS_BuildCircuitISM> CircuitComponentClass;
	UPROPERTY(EditDefaultsOnly, Category = "Build")
	TArray<FCircuitComponents> CircuitComponentsArray;
	UPROPERTY(EditDefaultsOnly, Category = "Build")
	UMaterialInstance* MaterialValid;
	UPROPERTY(EditDefaultsOnly, Category = "Build")
	UMaterialInstance* MaterialInvalid;
	
	int CircuitMeshIndex;
	bool bMaterialIsValid;
	bool bIsTargetingInstance;

	ACS_BuildCircuitISM* GetHitISMActor(const FHitResult& f_HitResult);

	void SetComponentGhostMaterial(bool f_bValidLocation);
	bool CheckOverlappedActors();
	bool CheckOverlappedComponents();
	void CheckPoweredActors();

	FGameplayTagContainer CurrentIDTags;
	FGameplayTagContainer CurrentBlockingTags;

	UPROPERTY()
	UStaticMeshComponent* CurrentHitMesh;
	UPROPERTY()
	FName CurrentHitSocket;
	UPROPERTY()
	AActor* CurrentHitActor;
	UPROPERTY()
	ACS_BuildCircuitBase* BuildBase;
	UPROPERTY()
	ACS_BuildCircuitISM* TargetedComponent;

};
