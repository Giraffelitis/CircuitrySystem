// Copyright 2023 by Pace Abbott. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CS_DataTypes.h"
#include "CS_CircuitComponentBase.generated.h"

class UCS_ISMComponent;
class ACS_PowerCable;
class ACS_LaserReceiver;
class ACS_LaserEmitter;
class UCS_TaggingSystem;

UCLASS()
class CIRCUITRYSYSTEM_API ACS_CircuitComponentBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACS_CircuitComponentBase();

	UPROPERTY(EditDefaultsOnly, Category = "Circuitry")
	UCS_ISMComponent* CircuitBoardInstancedMesh;
	UPROPERTY(EditDefaultsOnly, Category = "Circuitry")
	UCS_ISMComponent* SocketBlockInstancedMesh;
	UPROPERTY(EditDefaultsOnly, Category = "Circuitry")
	TSubclassOf<ACS_LaserEmitter> LaserEmitter;
	UPROPERTY(EditDefaultsOnly, Category = "Circuitry")
	TSubclassOf<ACS_LaserReceiver> LaserReceiver;
	UPROPERTY(EditDefaultsOnly, Category = "Circuitry")
	TSubclassOf<ACS_PowerCable> PowerCable;

	UPROPERTY(VisibleAnywhere)
	UCS_TaggingSystem* TaggingSystemComp;
	
	int TotalNumOfParts = 0;
	TArray<FName> InstanceSocketsArray;
	
	UFUNCTION(BlueprintCallable, Category = "Circuitry")
	void DestroyInstance(const FHitResult f_HitResult);

	int GetHitISMComponentIndex(const FHitResult f_HitResult);

	bool IsValidSocket(UInstancedStaticMeshComponent* f_HitComponent, const FName& f_Filter, const FName& f_SocketName);
	
	FTransform GetHitSocketTransform(const FHitResult& f_HitResult, const FName& f_Filter, float f_ValidHitDistance = 200.0f);

	void AddInstanceToActor(const FTransform& f_ActorTransform, ECircuitComponentType f_CircuitCompType, FGameplayTagContainer& f_BlockingTags);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

FTransform GetISMSocketTransform(UInstancedStaticMeshComponent* f_ISMComponent, int32 f_ISMIndex, const FName& f_SocketName);
};
