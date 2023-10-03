// Copyright 2023 by Pace Abbott. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "CS_PowerableBase.h"
#include "CS_PowerBlock.generated.h"

class UCS_AttachPoint;

/**
 * 
 */
UCLASS()
class ACS_PowerBlock : public ACS_PowerableBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	UCS_AttachPoint* AttachPoint_1;
	UPROPERTY(EditAnywhere)
	UCS_AttachPoint* AttachPoint_2;
	UPROPERTY(EditAnywhere)
	UCS_AttachPoint* AttachPoint_3;
	UPROPERTY(EditAnywhere)
	UCS_AttachPoint* AttachPoint_4;

public:
	ACS_PowerBlock();

	virtual void BeginPlay() override;

	
};
