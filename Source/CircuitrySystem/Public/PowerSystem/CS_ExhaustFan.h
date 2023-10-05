// Copyright 2023 by Pace Abbott. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "CS_PowerableBase.h"
#include "CS_ExhaustFan.generated.h"

UCLASS()
class CIRCUITRYSYSTEM_API ACS_ExhaustFan : public ACS_PowerableBase
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ACS_ExhaustFan();

	virtual void BeginPlay() override;
	void UpdatePowerState();
	virtual void IsPowered_Implementation(AActor* f_Actor) override;
	virtual void IsNotPowered_Implementation(AActor* f_Actor) override;
	void StartFanTimer();
	void SpinFan();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* FanHousing;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* FanBlade;
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* PowerSocket;
	
	UPROPERTY(EditAnywhere)
	bool bFanIsRunning;

	FTimerHandle FanTimerHandle;
};
