// Copyright 2023 by Pace Abbott. All Rights Reserved.


#include "CS_LaserEmitter.h"
#include "Components/ArrowComponent.h"

// Sets default values
ACS_LaserEmitter::ACS_LaserEmitter()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>("BaseMesh");
	RootComponent = BaseMesh;

	RightSupport = CreateDefaultSubobject<UStaticMeshComponent>("RightSupport");
	RightSupport->SetupAttachment(BaseMesh);

	LeftSupport = CreateDefaultSubobject<UStaticMeshComponent>("Left Support");
	LeftSupport->SetupAttachment(BaseMesh);
	
	Cylinder = CreateDefaultSubobject<UStaticMeshComponent>("Cylinder");
	Cylinder->SetupAttachment(BaseMesh);
	
	Arrow = CreateDefaultSubobject<UArrowComponent>("Arrow");
	Arrow->SetupAttachment(BaseMesh);
}

// Called when the game starts or when spawned
void ACS_LaserEmitter::BeginPlay()
{
	Super::BeginPlay();

	MaxLaserDistance =50000.0f;		
	CollisionChannel = ECC_WorldDynamic;	
	ObjectQueryParams.AddObjectTypesToQuery(CollisionChannel);	
	
}

// Called every frame
void ACS_LaserEmitter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	StartLocation = Arrow->GetComponentLocation();
	EndLocation =  Arrow->GetForwardVector() * MaxLaserDistance + StartLocation;
	
	// Sets debug info colors
	LineColor = bBlockingHit ? FColor::Green : FColor::Red;

	bBlockingHit = GetWorld()->LineTraceSingleByChannel(HitActor, StartLocation, EndLocation, CollisionChannel);

	if (bDebugDraw)
	{
		DrawDebugLine(GetWorld(), StartLocation, EndLocation, LineColor, false, 0.1f);
	}

}

