// Copyright 2023 by Pace Abbott. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "CS_PowerBase.h"
#include "CS_Light.generated.h"

class APointLight;
class ACS_LaserReceiver;

/**
 * 
 */
UCLASS()
class ACS_Light : public ACS_PowerBase
{
	GENERATED_BODY()

public:
	ACS_Light();
	
	virtual void HasPower() override;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* BaseMesh;
	
	UPROPERTY(EditAnywhere)
	APointLight* Light;

	UPROPERTY(EditAnywhere)
	ACS_LaserReceiver* LaserReceiver;

private:
	FAttachmentTransformRules* AttachRules;
};
