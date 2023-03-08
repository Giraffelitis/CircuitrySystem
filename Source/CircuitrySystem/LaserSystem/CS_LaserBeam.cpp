// Copyright 2023 by Pace Abbott. All Rights Reserved.


#include "CS_LaserBeam.h"

#include "CS_TaggingSystem.h"

ACS_LaserBeam::ACS_LaserBeam()
{
	BaseMesh = CreateDefaultSubobject<UStaticMesh>("BaseMesh");

	TaggingSystemComp = CreateDefaultSubobject<UCS_TaggingSystem>("TaggingSystemComp");

	this->SetMobility(EComponentMobility::Movable);
	this->SetActorEnableCollision(false);
}

void ACS_LaserBeam::SetLaserBeamTransform(FTransform f_NewTransform)
{
	this->SetActorTransform(f_NewTransform);
}
