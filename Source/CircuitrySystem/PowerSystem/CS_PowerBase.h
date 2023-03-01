// Copyright 2023 by Pace Abbott. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "CS_PoweredInterface.h"
#include "GameFramework/Actor.h"
#include "CS_PowerBase.generated.h"

class UCS_PowerComponent;
UCLASS()
class ACS_PowerBase : public AActor, public ICS_PoweredInterface
{
	GENERATED_BODY()
	
protected:	
	// Sets default values for this actor's properties
	ACS_PowerBase();

	virtual void IsPowered_Implementation() override;
	
	UFUNCTION(BlueprintCallable)
	virtual void HasPower() {};

	UPROPERTY(EditAnywhere)
	UCS_PowerComponent* PowerComponent;


};
