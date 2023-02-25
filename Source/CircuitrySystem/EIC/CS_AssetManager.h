// Copyright 2023 by Pace Abbott. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/AssetManager.h"
#include "CS_AssetManager.generated.h"

/**
 * 
 */
UCLASS()
class CIRCUITRYSYSTEM_API UCS_AssetManager : public UAssetManager
{
	GENERATED_BODY()

public:

	UCS_AssetManager();

	// Returns the AssetManager singleton object.
	static UCS_AssetManager& Get();

protected:

	virtual void StartInitialLoading() override;
};
