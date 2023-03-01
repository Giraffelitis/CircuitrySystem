// Copyright 2023 by Pace Abbott. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "CS_PoweredInterface.h"
#include "Components/ActorComponent.h"
#include "CS_PowerComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UCS_PowerComponent : public UActorComponent, public ICS_PoweredInterface
{
	GENERATED_BODY()

public:
	
	virtual void IsPowered_Implementation() override;
	
};
