// Copyright 2023 by Pace Abbott. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CS_PowerComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class UCS_PowerComponent : public UActorComponent
{
	GENERATED_BODY()
	
protected:	
	UCS_PowerComponent();

public:
	UPROPERTY()
	TArray<AActor*> ReceivingPowerFromArray;
	UPROPERTY(EditAnywhere)
	bool bIsPowered;

};
