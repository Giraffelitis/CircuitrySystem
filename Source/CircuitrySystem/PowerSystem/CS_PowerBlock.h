// Copyright 2023 by Pace Abbott. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "CS_PoweredInterface.h"
#include "CS_TaggingSystem.h"
#include "GameFramework/Actor.h"
#include "CS_PowerBlock.generated.h"

class UCS_TaggingSystem;
class UCS_PowerComponent;

/**
 * 
 */
UCLASS()
class ACS_PowerBlock : public AActor, public ICS_PoweredInterface
{
	GENERATED_BODY()

public:
	ACS_PowerBlock();

	virtual void BeginPlay() override;
	
	void UpdatedPower();
	virtual void IsPowered_Implementation() override;
	virtual void IsNotPowered_Implementation() override;
	virtual void CheckPoweredState_Implementation() override;

	UPROPERTY(EditAnywhere)
	UCS_PowerComponent* PowerComp;
	UPROPERTY()
	UCS_TaggingSystem* TaggingSystemComp;
	UPROPERTY()
	TArray<FName> SocketsArray;
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* BaseMesh;
	
protected:


	



};
