// Copyright 2023 by Pace Abbott. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "CS_ReflectiveInterface.generated.h"

// This class does not need to be modified.
UINTERFACE()
class UCS_ReflectiveInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class CIRCUITRYSYSTEM_API ICS_ReflectiveInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual bool IsReflective();

};
