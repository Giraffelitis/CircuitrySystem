// Copyright 2023 by Pace Abbott. All Rights Reserved.


#include "CS_LaserEmitter.h"
#include "CS_LaserBeam.h"
#include "CS_TaggingSystem.h"
#include "Macros.h"
#include "CircuitrySystem/PowerSystem/CS_PowerComponent.h"
#include "CircuitrySystem/PowerSystem/CS_PoweredInterface.h"
#include "Components/ArrowComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "PhysicalMaterials/PhysicalMaterial.h"

// Sets default values
ACS_LaserEmitter::ACS_LaserEmitter()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SceneComp = CreateDefaultSubobject<USceneComponent>("RootComponent");
	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>("BaseMesh");
	BaseMesh->SetupAttachment(SceneComp);
	
	Arrow = CreateDefaultSubobject<UArrowComponent>("Arrow");
	Arrow->SetupAttachment(BaseMesh);
	TaggingSystemComp = CreateDefaultSubobject<UCS_TaggingSystem>("TaggingSystemComp");
	PowerComp = CreateDefaultSubobject<UCS_PowerComponent>("PowerComp");
	MaxLaserDistance = 1000.0f;
	MaxDeflections = 2;
	
}

// Called when the game starts or when spawned
void ACS_LaserEmitter::BeginPlay()
{
	Super::BeginPlay();
			
	CollisionChannel = ECC_GameTraceChannel1;
	ObjectQueryParams.AddObjectTypesToQuery(CollisionChannel);
	
	// Create a Beam mesh for each possible Deflection	
	for( int i = 0; i <= MaxDeflections ; i++ )
	{		
		BeamArray.Add(SpawnBeam());
	}	
}

void ACS_LaserEmitter::IsPowered_Implementation()
{
	if(!PowerComp->bIsPowered)
	{
		PowerComp->bIsPowered = true;
		
	}
}

void ACS_LaserEmitter::IsNotPowered_Implementation()
{
	if(PowerComp->bIsPowered)
	{
		PowerComp->bIsPowered = false;
	}
}

ACS_LaserBeam* ACS_LaserEmitter::SpawnBeam()
{
	FVector LaserDefaultLocation =  Arrow->GetComponentLocation() - FVector(15.0f, 0.0f, 0.0f);
	FRotator LaserDefaultRotation = Arrow->GetComponentRotation();
	ACS_LaserBeam* Beam = GetWorld()->SpawnActor<ACS_LaserBeam>(LaserBeamClass, LaserDefaultLocation, LaserDefaultRotation);
	if(!IsValid(Beam))
		return nullptr;
	
		Beam->SetMobility(EComponentMobility::Movable);
	
	return Beam;
	
}

// Called every frame
void ACS_LaserEmitter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if(PowerComp->bIsPowered)
	{
		GenerateLaser();
	}
	else
	{
		for(int i = 0; i < BeamArray.Num(); i++)
		{
			HideBeam(i);
		}
	}
}

void ACS_LaserEmitter::GenerateLaser()
{
	/** Set Variables for Initial Line Trace **/
	FVector TraceStart = Arrow->GetComponentLocation();
	FVector TraceEnd =  Arrow->GetForwardVector() * MaxLaserDistance + TraceStart;
	FCollisionQueryParams QueryParams;
	QueryParams.bReturnPhysicalMaterial = true;
	QueryParams.AddIgnoredActor(this);
	QueryParams.AddIgnoredActor(Cast<ACS_LaserBeam>(LaserBeamClass));
	TArray<FHitResult> OutHitArray;
	float TotalBeamLength = 0;
	bool bDoesLaserBounce = false;
	
	StartLaserTrace(TraceStart, TraceEnd, QueryParams, OutHitArray, PreviousHitArray, TotalBeamLength, bDoesLaserBounce, 0);
	
	for(int i = 1; i <= MaxDeflections; i++)
	{		
		if(bDoesLaserBounce)
		{
			bDoesLaserBounce = false;
			StartLaserTrace(TraceStart, TraceEnd, QueryParams, OutHitArray, PreviousHitArray, TotalBeamLength, bDoesLaserBounce, i);
		}
		else
			HideBeam(i);
	}
	PreviousHitArray = OutHitArray;
}

void ACS_LaserEmitter::StartLaserTrace(FVector &f_TraceStart, FVector &f_TraceEnd, FCollisionQueryParams f_QueryParams, TArray<FHitResult> &f_OutHitArray, TArray<FHitResult> &f_PreviousHitArray, float &f_TotalBeamLength, bool &f_bDoesLaserBounce, int Index)
{
	float BeamLength;
	FVector BeamTraceStart = f_TraceStart;
	FVector BeamTraceEnd = f_TraceEnd;
	int NumOfDeflects = Index;

	const FVector LaserDirectionVector = UKismetMathLibrary::GetDirectionUnitVector(f_TraceStart, f_TraceEnd);
	
	if(Index > 0)
		f_QueryParams.AddIgnoredActor(f_OutHitArray[Index -1].GetActor());
	
	FHitResult OutHit;	

	/** Initial Line Trace **/
	bool bBlockingHit = GetWorld()->LineTraceSingleByChannel(OutHit, f_TraceStart, f_TraceEnd, CollisionChannel, f_QueryParams);

	 BeamTraceStart = f_TraceStart;	 
	
	if(bBlockingHit)
	{
		BeamTraceEnd = OutHit.Location;		

		if(OutHit.PhysMaterial != nullptr)
		{
			if(OutHit.PhysMaterial->SurfaceType == EPhysicalSurface::SurfaceType1) // ReflectiveMaterial
			{
					f_TraceStart = OutHit.Location;
					f_TraceEnd = FMath::GetReflectionVector(LaserDirectionVector, OutHit.Normal) * (MaxLaserDistance - OutHit.Distance)  + f_TraceStart;
					f_bDoesLaserBounce = true;
			}
			if(OutHit.PhysMaterial->SurfaceType.GetValue() == EPhysicalSurface::SurfaceType2) // PoweredMaterial
			{
				if(OutHit.GetActor()->Implements<UCS_PoweredInterface>())
					ICS_PoweredInterface::Execute_IsPowered(OutHit.GetActor());
			}
		}
	}
	
	/** Collect Results for Initial Line Trace and update Beam Mesh Transform **/
	f_OutHitArray.Add(OutHit);
	f_TotalBeamLength += OutHit.Distance;
	BeamLength = OutHit.Distance / 10.0f;
	
	ShowBeam(NumOfDeflects, BeamLength, f_TotalBeamLength, BeamTraceStart, BeamTraceEnd);
	
	CheckForLostActors(f_PreviousHitArray,f_OutHitArray);
	
}


void ACS_LaserEmitter::ShowBeam(int f_ArrayIndex, float f_BeamLength, float f_TotalBeamLength, FVector f_TraceStart, FVector f_TraceEnd)
{
	if (f_BeamLength <= 0)
		f_BeamLength = (MaxLaserDistance - f_TotalBeamLength) / 10.0f;
	
	const FVector LaserScale = FVector(f_BeamLength, 1.0f, 1.0f);
	const FRotator LaserRotation = UKismetMathLibrary::FindLookAtRotation(f_TraceStart, f_TraceEnd);
	const FTransform UpdateTransform = FTransform( LaserRotation, f_TraceStart, LaserScale);	

	BeamArray[f_ArrayIndex]->SetActorTransform(UpdateTransform);
	BeamArray[f_ArrayIndex]->SetActorHiddenInGame(false);
}


void ACS_LaserEmitter::HideBeam(int f_ArrayIndex)
{
	BeamArray[f_ArrayIndex]->SetActorHiddenInGame(true);
}

void ACS_LaserEmitter::CheckForLostActors(TArray<FHitResult> f_PreviousHitArray, TArray<FHitResult> f_OutHitArray)
{
	TArray<AActor*> TempActorArray;

	// Loop through current hit actors and add unique to array to check against previous hit actors
	for(FHitResult PreviousHitResult : f_PreviousHitArray)
	{
		AActor* TempActor = PreviousHitResult.GetActor();
		if(IsValid(TempActor))
			TempActorArray.AddUnique(TempActor);	
	}

	TArray<AActor*> LostActorArray;
	for(FHitResult CurrentHitResult : f_OutHitArray)
	{
		if(TempActorArray.Num() > 0)
		{
			bool bIsMatch = TempActorArray.Contains(CurrentHitResult.GetActor());
			if(!bIsMatch)
			{
				for(AActor* TempActor : TempActorArray)
				{
					if(TempActor!= CurrentHitResult.GetActor())
					{
						LostActorArray.AddUnique(TempActor);
					}
					else if (TempActor == CurrentHitResult.GetActor() && LostActorArray.Contains(CurrentHitResult.GetActor()))
					{
						TempActorArray.Remove(TempActor);
					}
				}				
			}
		}
	}
	if(LostActorArray.Num() > 0)
	{
		for(AActor* LostActor : LostActorArray)
		{
			if(LostActor->Implements<UCS_PoweredInterface>())
			{
				ICS_PoweredInterface::Execute_IsNotPowered(LostActor);
			}
		}
	}
}

void ACS_LaserEmitter::Destroyed()
{
	Super::Destroyed();

	for( int i = 0; i < BeamArray.Num() ; i++ )
	{		
		BeamArray[i]->Destroy();
	}	
}
