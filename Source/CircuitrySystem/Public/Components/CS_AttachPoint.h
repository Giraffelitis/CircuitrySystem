// Copyright 2023 by Pace Abbott. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "CS_AttachPoint.generated.h"

class UCS_TaggingSystem;
class USphereComponent;

DECLARE_MULTICAST_DELEGATE_TwoParams(FAttachPointUpdate, bool, AActor*);

DECLARE_MULTICAST_DELEGATE(FAttachPointAttachableRemoved);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CIRCUITRYSYSTEM_API UCS_AttachPoint : public USceneComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UCS_AttachPoint();
	
	UPROPERTY(VisibleAnywhere)
	UCS_TaggingSystem* TagComp;
	UPROPERTY()
	ACS_AttachableActor* AttachedActor;
	
	FAttachPointUpdate AttachPointUpdate;
	
	FAttachPointAttachableRemoved AttachPointAttachableRemoved;
	FTimerHandle DetectAttachableTimerHandle;
	float MaxDetectAttachableTime = 0.5f;

	UFUNCTION()
	virtual void OnAttachActor(ACS_AttachableActor* f_AttachActor);
	UFUNCTION()
	virtual void OnDetachActor(ACS_AttachableActor* f_AttachActor);
	
protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	void StartAttachableActorTimer();
	void CancelAttachableActorTimer();
	UFUNCTION()
	void DetectAttachableActors();





};
