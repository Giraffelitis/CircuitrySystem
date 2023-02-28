// Copyright 2023 by Pace Abbott. All Rights Reserved.


#include "CS_LaserEmitter.h"
#include "CS_LaserBeam.h"
#include "CS_ReflectiveInterface.h"
#include "Editor.h"
#include "VectorTypes.h"
#include "BehaviorTree/BehaviorTreeTypes.h"
#include "Components/ArrowComponent.h"
#include "Kismet/KismetMathLibrary.h"

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

	MaxLaserDistance = 1000.0f;
	MaxDeflections = 2;
}

// Called when the game starts or when spawned
void ACS_LaserEmitter::BeginPlay()
{
	Super::BeginPlay();
			
	CollisionChannel = ECC_WorldDynamic;
	ObjectQueryParams.AddObjectTypesToQuery(CollisionChannel);
	
	// Create a Beam mesh for each possible Deflection	
	for( int i = 0; i <= MaxDeflections ; i++ )
	{		
		BeamArray.Add(SpawnBeam());
	}	
}

ACS_LaserBeam* ACS_LaserEmitter::SpawnBeam()
{
	LaserDefaultLocation =  Arrow->GetComponentLocation() - FVector(15.0f, 0.0f, 0.0f);
	LaserDefaultRotation = Arrow->GetComponentRotation();
	ACS_LaserBeam* Beam = GetWorld()->SpawnActor<ACS_LaserBeam>(LaserBeam_Class, LaserDefaultLocation, LaserDefaultRotation);
	Beam->SetMobility(EComponentMobility::Movable);
	return Beam;
}

void ACS_LaserEmitter::ShowBeam(int ArrayIndex, FTransform NewTransform)
{
	BeamTransform = NewTransform;
	BeamArray[ArrayIndex]->SetActorTransform(BeamTransform);
	BeamArray[ArrayIndex]->SetActorHiddenInGame(false);
}

void ACS_LaserEmitter::HideBeam(int ArrayIndex)
{
	BeamArray[ArrayIndex]->SetActorHiddenInGame(true);
}

// Called every frame
void ACS_LaserEmitter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	GenerateLaser();
}

void ACS_LaserEmitter::GenerateLaser()
{
	/** Set Variables for Initial Line Trace **/
	FVector TraceStart = Arrow->GetComponentLocation();
	FVector TraceEnd =  Arrow->GetForwardVector() * MaxLaserDistance + TraceStart;
	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(this);
	QueryParams.AddIgnoredActor(Cast<ACS_LaserBeam>(LaserBeam_Class));	
	TArray<FHitResult> OutHitArray;
	float TotalBeamLength;

	bool bLaserDidHit = StartLaserTrace(TraceStart, TraceEnd, QueryParams, OutHitArray, TotalBeamLength, 0);
	
	for(int i = 1; i <= MaxDeflections; i++)
	{		
		if(bLaserDidHit)
		{
			bLaserDidHit = StartLaserTrace(TraceStart, TraceEnd, QueryParams, OutHitArray, TotalBeamLength, i);
		}
		else
			HideBeam(i);
	}
}

bool ACS_LaserEmitter::StartLaserTrace(FVector &TraceStart, FVector &TraceEnd, FCollisionQueryParams QueryParams, TArray<FHitResult> &OutHitArray, float &TotalBeamLength, int Index)
{
	float BeamLength;
	int NumOfDeflects = Index;
	const FVector LaserDirectionVector = UKismetMathLibrary::GetDirectionUnitVector(TraceStart, TraceEnd);
	
	if(Index > 0)
		QueryParams.AddIgnoredActor(OutHitArray[Index -1].GetActor());
	
	FHitResult OutHit;	

	/** Initial Line Trace **/
	bool bBlockingHit = GetWorld()->LineTraceSingleByChannel(OutHit, TraceStart, TraceEnd, CollisionChannel, QueryParams);
	
	if(bBlockingHit)
	{
		/** Collect Results for Initial Line Trace and update Beam Mesh Transform **/
		OutHitArray.Add(OutHit);
		BeamLength = OutHit.Distance / 10.0f;
		TotalBeamLength += BeamLength;
		FVector LaserScale = FVector(BeamLength, 1.0f, 1.0f);
		FRotator LaserRotation = UKismetMathLibrary::FindLookAtRotation(TraceStart, TraceEnd);
		FTransform UpdateTransform = FTransform(LaserRotation, TraceStart, LaserScale);
		ShowBeam(NumOfDeflects, UpdateTransform);

		TraceStart = OutHit.Location;
		TraceEnd = FMath::GetReflectionVector(LaserDirectionVector, OutHit.Normal) * ((MaxLaserDistance - TotalBeamLength) * 10)  + TraceStart;
		bool bIsImplemented = OutHit.GetActor()->Implements<UCS_ReflectiveInterface>();
		
		return bIsImplemented;
	}
	
	BeamLength = MaxLaserDistance - TotalBeamLength;
	FVector LaserScale = FVector(BeamLength, 1.0f, 1.0f);
	FRotator LaserRotation = UKismetMathLibrary::FindLookAtRotation(TraceStart, TraceEnd);
	FTransform UpdateTransform = FTransform( LaserRotation, TraceStart, LaserScale);		
	ShowBeam(NumOfDeflects, UpdateTransform);
	
	return bBlockingHit; 
}

