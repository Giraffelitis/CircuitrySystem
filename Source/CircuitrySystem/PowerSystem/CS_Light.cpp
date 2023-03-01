// Copyright 2023 by Pace Abbott. All Rights Reserved.


#include "CS_Light.h"

#include "Macros.h"
#include "Engine/PointLight.h"

ACS_Light::ACS_Light()
{
	Light = CreateDefaultSubobject<APointLight>("Light");
}
void ACS_Light::HasPower()
{	
	Light->SetLightColor(FLinearColor(100.0f,100.0f,100.0f,1.0f));

#if !UE_BUILD_SHIPPING
	PRINT(-1, 1.0f, FColor::Black, "Light Powered");
#endif
	
}
