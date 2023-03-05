// Copyright 2023 by Pace Abbott. All Rights Reserved.

#pragma once

#include "CS_DataTypes.generated.h"

UENUM(BlueprintType)
enum class ECircuitComponentType : uint8
{
	Base			UMETA(DisplayName = "Base"),
	Jumper			UMETA(DisplayName = "Jumper"),
	Laser			UMETA(DisplayName = "Laser"),
	Receiver		UMETA(DisplayName = "Receiver"),
	SocketBlock		UMETA(DisplayName = "SocketBlock"),
	Switch			UMETA(DisplayName = "Switch")
	
};

USTRUCT(BlueprintType)
struct FCircuitComponents
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, Category = "Circuitry")
	UStaticMesh* CircuitMesh;

	UPROPERTY(EditDefaultsOnly, Category = "Circuitry")
	ECircuitComponentType CircuitComponentType;
};