// Fill out your copyright notice in the Description page of Project Settings.


#include "CS_PlayerCharacter.h"
#include "CS_PlayerController.h"
#include "Camera/CameraComponent.h"
#include "Components/ArrowComponent.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"


// Sets default values
ACS_PlayerCharacter::ACS_PlayerCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	Camera = this->FindComponentByClass<UCameraComponent>();

	GrabLocation = CreateDefaultSubobject<UArrowComponent>("Grab Location");
	GrabLocation->SetupAttachment(Camera);

	PhysicsHandle = CreateDefaultSubobject<UPhysicsHandleComponent>("Physics Handle");

	//Is character carrying an object in front of it?
	bItemPickedUp = false;
	//Distance objects are held in front of character
	ObjectHeldDistance = 200.0f;

	//How fast the object rotates
	RotationDegree = 1.0f;
	
	//Picked up object Dampening;
	AdjustedDampening = 1000.0f;

	// Maximum distance away and object can be picked up from
	PickupDistance = 300.0f;
	
}

// Called when the game starts or when spawned
void ACS_PlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	
}

// Called every frame
void ACS_PlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	//Does character have something picked up?
	if(bItemPickedUp)
	{
		//Move object to Grab location and change its linear dampening
		PhysicsHandle->SetTargetLocationAndRotation(GetActorLocation() + (GetViewRotation().Vector() * ObjectHeldDistance) , CarriedObjectRoation);
	}
	
}

// Called to bind functionality to input
void ACS_PlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	
}
	
void ACS_PlayerCharacter::PickupAction()
{
	APlayerCameraManager* PlayerCamera = GetWorld()->GetFirstPlayerController()->PlayerCameraManager;
	
	//Object Hit
	FHitResult OutHit;

	//Trace starting point
	FVector StartLocation = PlayerCamera->GetCameraLocation();

	//Trace ending point
	FVector EndLocation = (PlayerCamera->GetActorForwardVector() * PickupDistance) + StartLocation;

	//Trace Collision channels
	ECollisionChannel CollisionChannel = ECC_WorldDynamic;

	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(this);
	
	//Are our hands empty	
	if(!bItemPickedUp)
	{
		//LineTrace to detect object
		GetWorld()->LineTraceSingleByChannel(OutHit, StartLocation, EndLocation, CollisionChannel, QueryParams);
		UPrimitiveComponent* HitComponent = OutHit.GetComponent();

		if(IsValid(HitComponent))
		{			
			//Check if object is Simulating Physics
			if(HitComponent->IsSimulatingPhysics())
			{
				//Grab Object change its collision and dampening
				PhysicsHandle->GrabComponentAtLocationWithRotation(HitComponent, FName() , HitComponent->GetComponentLocation() , FRotator(HitComponent->GetRelativeRotation()));
				DefaultDampening = PhysicsHandle->GetGrabbedComponent()->GetLinearDamping();
				PhysicsHandle->GetGrabbedComponent()->SetCollisionResponseToChannel(ECC_Pawn, ECR_Ignore);
				PhysicsHandle->GetGrabbedComponent()->SetAngularDamping(AdjustedDampening);
				CarriedObjectRoation = HitComponent->GetRelativeRotation();
				bItemPickedUp = true;
			}			
		}
	}
	else
	{
		//Restore objects collision and dampening and drop it.
		PhysicsHandle->GetGrabbedComponent()->SetAngularDamping(DefaultDampening);
		PhysicsHandle->GetGrabbedComponent()->SetCollisionResponseToChannel(ECC_Pawn, ECR_Block);
		PhysicsHandle->ReleaseComponent();
		bItemPickedUp = false;
	}
}

void ACS_PlayerCharacter::PrimarySupportAction()
{
	//Rotates Object being held
	if(bItemPickedUp)
	{
		if(InputModifier)
		{
			CarriedObjectRoation.Pitch += RotationDegree;
		}
		else
		{
			CarriedObjectRoation.Yaw += RotationDegree;
		}
	}
}
void ACS_PlayerCharacter::SecondarySupportAction()
{
	//Counter Rotates Object being held
	if(bItemPickedUp)
	{
		if(InputModifier)
		{
			CarriedObjectRoation.Pitch -= RotationDegree;
		}
		else
		{
			CarriedObjectRoation.Yaw -= RotationDegree;
		}
	}
}

