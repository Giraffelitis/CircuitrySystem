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
	
}

// Called when the game starts or when spawned
void ACS_PlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	//Picked up object Dampening;
	AdjustedDampening = 1000.0f;

	// Maximum distance away and object can be picked up from
	PickupDistance = 300.0f;
}

void ACS_PlayerCharacter::PickupAction()
{
	//Object Hit
	FHitResult OutHit;

	//Trace starting point
	FVector StartLocation = Camera->GetComponentLocation();

	//Trace ending point
	FVector EndLocation = (Camera->GetForwardVector() * PickupDistance) + StartLocation;

	//Trace Collision channels
	ECollisionChannel CollisionChannel = ECC_WorldDynamic;
	
	//Are our hands empty	
	if(!bItemPickedUp)
	{
		//Linetrace to detect object
		bItemPickedUp = GetWorld()->LineTraceSingleByChannel(OutHit, StartLocation, EndLocation, CollisionChannel);

		//Check if object is Simulating Physics
		if(OutHit.Component->IsSimulatingPhysics())
		{
			//Grab Object change its collision and dampening
			PhysicsHandle->GrabComponentAtLocation(OutHit.GetComponent(), FName() ,GrabLocation->GetComponentLocation());
			DefaultDampening = PhysicsHandle->GetGrabbedComponent()->GetLinearDamping();
			PhysicsHandle->GetGrabbedComponent()->SetCollisionResponseToChannel(ECC_Pawn, ECR_Ignore);
			
		}
	}
	else
	{
		//Restore objects collision and dampening and drop it.
		PhysicsHandle->GetGrabbedComponent()->SetAngularDamping(DefaultDampening);
		PhysicsHandle->GetGrabbedComponent()->SetCollisionResponseToChannel(ECC_Pawn, ECR_Block);
		PhysicsHandle->ReleaseComponent();
	}
}



// Called every frame
void ACS_PlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//Does character have something picked up?
	if(bItemPickedUp)
	{
		//Move object to Grab location and change its linear dampening
		PhysicsHandle->SetTargetLocation(GrabLocation->GetComponentLocation());
		PhysicsHandle->GetGrabbedComponent()->SetAngularDamping(AdjustedDampening);
	}
}

// Called to bind functionality to input
void ACS_PlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	//Cast<ACS_PlayerController>(Controller)->SetupInput();
}
