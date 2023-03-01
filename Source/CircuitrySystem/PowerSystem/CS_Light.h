// Copyright 2023 by Pace Abbott. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "CS_PowerBase.h"
#include "CS_Light.generated.h"

class APointLight;
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
	UPROPERTY(EditAnywhere)
	APointLight* Light;
};
