// Copyright 2023 by Pace Abbott. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "CS_PowerBase.h"
#include "CS_PowerBlock.generated.h"

class APointLight;
class ACS_LaserReceiver;

/**
 * 
 */
UCLASS()
class ACS_PowerBlock : public ACS_PowerBase
{
	GENERATED_BODY()

public:
	ACS_PowerBlock();
	
	virtual void HasPower() override;
	virtual void LostPower() override;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* BaseMesh;
	
	UPROPERTY(EditAnywhere)
	TArray<AActor*> ConnectedActorsArray;

	UPROPERTY()
	APointLight* PointLight;

	UPROPERTY(EditAnywhere)
	ACS_LaserReceiver* LaserReceiver;


private:
	FAttachmentTransformRules* AttachRules;


};
