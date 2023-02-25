// Copyright 2023 by Pace Abbott. All Rights Reserved.


#include "CS_PowerBase.h"

// Sets default values
ACS_PowerBase::ACS_PowerBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ACS_PowerBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACS_PowerBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

