// Copyright 2023 by Pace Abbott. All Rights Reserved.

#pragma once
#include "GameplayTagContainer.h"
#include "Engine/DataTable.h"
#include "CS_DataTypes.generated.h"

UENUM(BlueprintType)
enum class ECircuitComponentType : uint8
{
	Base			UMETA(DisplayName = "Base"),
	Laser			UMETA(DisplayName = "Laser"),
	PowerCable		UMETA(DisplayName = "PowerCable"),
	Receiver		UMETA(DisplayName = "Receiver"),
	SocketBlock		UMETA(DisplayName = "SocketBlock"),
	Switch			UMETA(DisplayName = "Switch")
	
};

USTRUCT(BlueprintType)
struct FCircuitComponents : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, Category = "Circuitry")
	UStaticMesh* CircuitMesh;
	UPROPERTY(EditDefaultsOnly, Category = "Circuitry")
	ECircuitComponentType CircuitComponentType;
	UPROPERTY(EditDefaultsOnly, Category = "Circuitry")
	FName FilterCharacter;	
	UPROPERTY(EditDefaultsOnly, Category = "Circuitry")
	bool bCanRotateOnSocket;
	UPROPERTY(EditDefaultsOnly, Category = "Circuitry")
	FGameplayTagContainer MeshIDTags;
	UPROPERTY(EditDefaultsOnly, Category = "Circuitry")
	FGameplayTagContainer MeshBlockingTags;
};