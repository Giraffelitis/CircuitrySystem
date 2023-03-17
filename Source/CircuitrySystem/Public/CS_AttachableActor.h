// Copyright 2023 by Pace Abbott. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "CS_AttachPoint.h"
#include "CircuitrySystem/PowerSystem/CS_PoweredInterface.h"
#include "GameFramework/Actor.h"
#include "CS_AttachableActor.generated.h"

class UCS_PowerComponent;
class UCS_TaggingSystem;
UCLASS()
class CIRCUITRYSYSTEM_API ACS_AttachableActor : public AActor, public ICS_PoweredInterface
{
	GENERATED_BODY()

public:
	
	void UpdateAttachedState(UCS_AttachPoint* f_AttachPoint, bool f_bIsAttached);
	
	UPROPERTY()
	bool bIsAttached;
	UPROPERTY()
	AActor* AttachedToActor;
	UPROPERTY(EditAnywhere)
	UCS_PowerComponent* PowerComp;
	UPROPERTY(VisibleAnywhere)
	UCS_TaggingSystem* TaggingSystemComp;
	
protected:
	virtual void Destroyed() override;
};
