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

	bItemPickedUp = false;
	
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

// Called every frame
void ACS_PlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	//Does character have something picked up?
	if(bItemPickedUp)
	{
		FVector GrabLoc = (GrabLocation->GetComponentToWorld().GetLocation());
		FVector ForwardDirection = GetViewRotation().Vector();
		//Move object to Grab location and change its linear dampening
		PhysicsHandle->SetTargetLocationAndRotation(GetActorLocation() + (ForwardDirection * 200.0f) , CarriedObjectRoation);
		PhysicsHandle->GetGrabbedComponent()->SetAngularDamping(AdjustedDampening);

		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, ForwardDirection.ToString());
	}
	
}

// Called to bind functionality to input
void ACS_PlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	Cast<ACS_PlayerController>(Controller)->SetupInput();
}
