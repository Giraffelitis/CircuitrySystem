// Copyright 2023 by Pace Abbott. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "CS_PowerableBase.h"
#include "CS_Door.generated.h"

UCLASS()
class CIRCUITRYSYSTEM_API ACS_Door : public ACS_PowerableBase
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ACS_Door();
	virtual void BeginPlay() override;
	void UpdatePowerState();
	virtual void IsPowered_Implementation(AActor* f_Actor) override;
	virtual void IsNotPowered_Implementation(AActor* f_Actor) override;
	void StartDoorMovementTimer();
	void AdjustDoorPanelPosition();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* DoorFrame;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* LeftDoorPanel;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* RightDoorPanel;
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* PowerSocket;

	FVector RightDoorPanelClosedLocation;
	FVector LeftDoorPanelClosedLocation;
	FVector RightDoorPanelOpenLocation;
	FVector LeftDoorPanelOpenLocation;
	
	UPROPERTY(EditAnywhere)
	bool bDoorIsClosed;

	FTimerHandle DoorTimerHandle;

};
