// Copyright 2023 by Pace Abbott. All Rights Reserved.


#include "CS_LaserBeam.h"

ACS_LaserBeam::ACS_LaserBeam()
{
	BaseMesh = CreateDefaultSubobject<UStaticMesh>("BaseMesh");

	this->SetMobility(EComponentMobility::Movable);
	this->SetActorEnableCollision(false);
}

void ACS_LaserBeam::SetLaserBeamTransform(FTransform NewTransform)
{
	this->SetActorTransform(NewTransform);
}
