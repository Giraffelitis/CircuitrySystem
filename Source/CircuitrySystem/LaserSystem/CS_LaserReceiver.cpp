// Copyright 2023 by Pace Abbott. All Rights Reserved.


#include "CS_LaserReceiver.h"
#include "CircuitrySystem/PowerSystem/CS_PowerComponent.h"
#include "EnvironmentQuery/EnvQueryTypes.h"

// Sets default values
ACS_LaserReceiver::ACS_LaserReceiver()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>("BaseMesh");
	RootComponent = BaseMesh;

	SphereComponent = CreateDefaultSubobject<USphereComponent>("Sphere Component");
	SphereComponent->SetupAttachment(BaseMesh);
	SphereComponent->SetSphereRadius(632.0f);
	SphereComponent->SetCollisionResponseToAllChannels(ECR_Overlap);

	PowerComp = CreateDefaultSubobject<UCS_PowerComponent>("Power Comp");	
}

// Called when the game starts or when spawned
void ACS_LaserReceiver::BeginPlay()
{
	Super::BeginPlay();	
}

// Called every frame
void ACS_LaserReceiver::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);	
}