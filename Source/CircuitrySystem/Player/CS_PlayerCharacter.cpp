// Fill out your copyright notice in the Description page of Project Settings.


#include "CS_PlayerCharacter.h"
#include "CS_BuildHelperMesh.h"
#include "CS_CircuitComponentBase.h"
#include "CS_PlayerController.h"
#include "CS_TaggingSystem.h"
#include "Macros.h"
#include "Camera/CameraComponent.h"
#include "CircuitrySystem/EIC/CS_EnhancedInputComponent.h"
#include "CircuitrySystem/GameBase/CS_GameplayTags.h"
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

	//How fast the object rotates
	RotationDegree = 1.0f;
	
	//Picked up object Dampening;
	AdjustedDampening = 1000.0f;

	// Maximum distance away and object can be Interacted with
	InteractDistance = 300.0f;

	// Distance item is held in front of character
	CarryOffset = 300.0f;

	//Maximum distance away you can build
	MaxBuildDistance = 700.0f;
}

void ACS_PlayerCharacter::SetupPlayerInputComponent(UInputComponent* f_PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(f_PlayerInputComponent);

	check(InputComponent)
	UCS_EnhancedInputComponent* CSEnhancedInputComponent = Cast<UCS_EnhancedInputComponent>(InputComponent);

	//Make sure to set your input component class in the InputSettings->DefaultClasses
	if(!ensure(CSEnhancedInputComponent))
		return;	

	const FCS_GameplayTags& GameplayTags = FCS_GameplayTags::Get();

	//Bind Input actions by tag
	CSEnhancedInputComponent->BindActionByTag(InputConfig, GameplayTags.InputTag_Jump, ETriggerEvent::Triggered, this, &ACS_PlayerCharacter::Jump);
	CSEnhancedInputComponent->BindActionByTag(InputConfig, GameplayTags.InputTag_Crouch_Pressed, ETriggerEvent::Triggered, this, &ACS_PlayerCharacter::StartCrouch);	
	CSEnhancedInputComponent->BindActionByTag(InputConfig, GameplayTags.InputTag_Crouch_Released, ETriggerEvent::Triggered, this, &ACS_PlayerCharacter::EndCrouch);
	CSEnhancedInputComponent->BindActionByTag(InputConfig, GameplayTags.InputTag_Modifier_Alt_Pressed, ETriggerEvent::Triggered, this, &ACS_PlayerCharacter::ApplyAltModifier);
	CSEnhancedInputComponent->BindActionByTag(InputConfig, GameplayTags.InputTag_Modifier_Alt_Released, ETriggerEvent::Triggered, this, &ACS_PlayerCharacter::RemoveAltModifier);
	CSEnhancedInputComponent->BindActionByTag(InputConfig, GameplayTags.InputTag_Modifier_Alt_Pressed, ETriggerEvent::Triggered, this, &ACS_PlayerCharacter::ApplyAltModifier);
	CSEnhancedInputComponent->BindActionByTag(InputConfig, GameplayTags.InputTag_Modifier_Alt_Released, ETriggerEvent::Triggered, this, &ACS_PlayerCharacter::RemoveAltModifier);
	CSEnhancedInputComponent->BindActionByTag(InputConfig, GameplayTags.InputTag_MouseWheel_Up, ETriggerEvent::Triggered, this, &ACS_PlayerCharacter::InputMouseWheelUp);
	CSEnhancedInputComponent->BindActionByTag(InputConfig, GameplayTags.InputTag_MouseWheel_Down, ETriggerEvent::Triggered, this, &ACS_PlayerCharacter::InputMouseWheelDown);
	CSEnhancedInputComponent->BindActionByTag(InputConfig, GameplayTags.InputTag_Interaction_RotatePos, ETriggerEvent::Triggered, this, &ACS_PlayerCharacter::RotateObjectPos);
	CSEnhancedInputComponent->BindActionByTag(InputConfig, GameplayTags.InputTag_Interaction_RotateNeg, ETriggerEvent::Triggered, this, &ACS_PlayerCharacter::RotateObjectNeg);
	CSEnhancedInputComponent->BindActionByTag(InputConfig, GameplayTags.InputTag_Interaction_Pickup, ETriggerEvent::Triggered, this, &ACS_PlayerCharacter::PickupItem);
	CSEnhancedInputComponent->BindActionByTag(InputConfig, GameplayTags.InputTag_Build_ToggleBuild, ETriggerEvent::Triggered, this, &ACS_PlayerCharacter::ToggleBuildMode);
	CSEnhancedInputComponent->BindActionByTag(InputConfig, GameplayTags.InputTag_Build_SpawnComponent, ETriggerEvent::Triggered, this, &ACS_PlayerCharacter::SpawnBuildComponent);
	CSEnhancedInputComponent->BindActionByTag(InputConfig, GameplayTags.InputTag_Build_DestroyComponent, ETriggerEvent::Triggered, this, &ACS_PlayerCharacter::DestroyBuildComponent);

}

// Called every frame
void ACS_PlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if(bInBuildMode && BuildHelper)
	{
		BuildHelper->SetBuildPosition(BuildHelperLineTrace(MaxBuildDistance));
	}
	
	//Does character have something picked up?
	if(bItemPickedUp)
	{
		//Move object to Grab location and change its linear dampening
		PhysicsHandle->SetTargetLocationAndRotation(GetActorLocation() + (GetViewRotation().Vector() * CarryOffset) , CarriedObjectRotation);
	}	
}

void ACS_PlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	if(BuildClass)
	{
		BuildHelper = GetWorld()->SpawnActor<ACS_BuildHelperMesh>(BuildClass);
	}
}

#pragma region BaseInputFunctions
void ACS_PlayerCharacter::StartJump()
{
	Jump();
}

void ACS_PlayerCharacter::Jump()
{
	Super::Jump();
}

void ACS_PlayerCharacter::EndJump()
{
	StopJumping();
}

void ACS_PlayerCharacter::StopJumping()
{
	Super::StopJumping();
}

void ACS_PlayerCharacter::StartCrouch()
{
	Crouch(true);
}

void ACS_PlayerCharacter::Crouch(bool f_bClientSimulation)
{
	Super::Crouch(f_bClientSimulation);
}

void ACS_PlayerCharacter::EndCrouch()
{
	UnCrouch(true);
}

void ACS_PlayerCharacter::UnCrouch(bool f_bClientSimulation)
{
	Super::UnCrouch(f_bClientSimulation);
}

void ACS_PlayerCharacter::ApplyAltModifier()
{
	SetAltModifier(true);
}

void ACS_PlayerCharacter::RemoveAltModifier()
{
	SetAltModifier(false);
}

void ACS_PlayerCharacter::SetAltModifier(bool f_Enabled)
{
	AltModifier = f_Enabled;
}

void ACS_PlayerCharacter::ApplyShiftModifier()
{
	SetShiftModifier(true);
}

void ACS_PlayerCharacter::RemoveShiftModifier()
{
	SetShiftModifier(false);
}

void ACS_PlayerCharacter::SetShiftModifier(bool f_Enabled)
{
	ShiftModifier = f_Enabled;
}

void ACS_PlayerCharacter::InputMouseWheelUp(const FInputActionValue& f_InputActionValue)
{
	if(bInBuildMode)
	{
		BuildHelper->SetMeshArrayIndex(1);		
	}
}

void ACS_PlayerCharacter::InputMouseWheelDown(const FInputActionValue& f_InputActionValue)
{
	if(bInBuildMode)
	{
		BuildHelper->SetMeshArrayIndex(-1);		
	}
}

void  ACS_PlayerCharacter::FellOutOfWorld(const UDamageType& f_DmgType)
{
	OnDeath(true);
}

void ACS_PlayerCharacter::OnDeath(bool f_IsFellOut)
{
	APlayerController* PlayerController = GetController<APlayerController>();
	if (PlayerController)
	{
		PlayerController->RestartLevel();
	}
}
#pragma endregion

#pragma region Pickup Item Interaction
void ACS_PlayerCharacter::RotateObjectPos(const FInputActionValue& f_InputActionValue)
{
	//Rotates Object being held
	if(bItemPickedUp)
	{
		if(AltModifier)
		{
			CarriedObjectRotation.Pitch += RotationDegree;
		}
		else if (ShiftModifier)
		{
			CarriedObjectRotation.Roll += RotationDegree;
		}
		else
		{
			CarriedObjectRotation.Yaw += RotationDegree;
		}
	}
}

void ACS_PlayerCharacter::RotateObjectNeg(const FInputActionValue& f_InputActionValue)
{
	//Counter Rotates Object being held
	if(bItemPickedUp)
	{
		if(AltModifier)
		{
			CarriedObjectRotation.Pitch -= RotationDegree;
		}
		else if (ShiftModifier)
		{
			CarriedObjectRotation.Roll -= RotationDegree;
		}
		else
		{
			CarriedObjectRotation.Yaw -= RotationDegree;
		}
	}
}

void ACS_PlayerCharacter::PickupItem()
{
	//Are our hands empty	
	if(!bItemPickedUp)
	{
		
	APlayerCameraManager* PlayerCamera = GetWorld()->GetFirstPlayerController()->PlayerCameraManager;
	
	//Object Hit
	FHitResult OutHit;
	//Trace starting point
	FVector StartLocation = PlayerCamera->GetCameraLocation();
	//Trace ending point
	FVector EndLocation = (PlayerCamera->GetActorForwardVector() * InteractDistance) + StartLocation;
	//Trace Collision channels
	ECollisionChannel CollisionChannel = ECC_WorldDynamic;
	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(this);
	
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
				CarriedObjectRotation = HitComponent->GetRelativeRotation();
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
#pragma endregion

#pragma region Building
void ACS_PlayerCharacter::ToggleBuildMode()
{
	SetBuildMode(bInBuildMode = !GetBuildMode());
}

void ACS_PlayerCharacter::SetBuildMode(bool f_Enabled)
{
	bInBuildMode = f_Enabled;
	if(BuildHelper)
	{
		BuildHelper->SetActorHiddenInGame(!bInBuildMode);
	}
}

void ACS_PlayerCharacter::SpawnBuildComponent()
{
	if(bInBuildMode && BuildHelper)
	{
		BuildHelper->SpawnBuildingComponent();
	}
}

void ACS_PlayerCharacter::DestroyBuildComponent()
{
	//Are our hands empty	
	if(bInBuildMode)
	{
		APlayerCameraManager* PlayerCamera = GetWorld()->GetFirstPlayerController()->PlayerCameraManager;
		//Object Hit
		FHitResult OutHit;
		//Trace starting point
		FVector StartLocation = PlayerCamera->GetCameraLocation();
		//Trace ending point
		FVector EndLocation = (PlayerCamera->GetActorForwardVector() * InteractDistance) + StartLocation;
		//Trace Collision channels
		ECollisionChannel CollisionChannel = ECC_WorldDynamic;

		FCollisionQueryParams QueryParams;
		QueryParams.AddIgnoredActor(this);
		
		//LineTrace to detect object
		GetWorld()->LineTraceSingleByChannel(OutHit, StartLocation, EndLocation, CollisionChannel, QueryParams);
		AActor* HitActor = OutHit.GetActor();

		if(ACS_CircuitComponentBase* HitCircuit = Cast<ACS_CircuitComponentBase>(HitActor))
		{
			if(!IsValid(HitCircuit))
				return;
			if(HitCircuit->GetHitISMComponentIndex(OutHit) == 0)
			{
				HitCircuit->DestroyInstance(OutHit);
			}
			else
			{
				HitCircuit->DestroyInstance(OutHit);
			}
		}
		else
		{
			UActorComponent* ActorComp = HitActor->GetComponentByClass(UCS_TaggingSystem::StaticClass());
			UCS_TaggingSystem* TagComp = Cast<UCS_TaggingSystem>(ActorComp);

			if(!IsValid(TagComp))
				return;
		
			if(TagComp->BaseTagContainer.HasTag(FGameplayTag::RequestGameplayTag("BuildTag.Player")))
			{
				HitActor->Destroy();			
			}
		}
	}
}

FHitResult ACS_PlayerCharacter::BuildHelperLineTrace(float f_MaxBuildDistance)
{
	APlayerCameraManager* PlayerCamera = GetWorld()->GetFirstPlayerController()->PlayerCameraManager;
	
	FHitResult OutHit;
	FVector StartLocation = PlayerCamera->GetCameraLocation();
	FVector EndLocation = (PlayerCamera->GetActorForwardVector() * f_MaxBuildDistance) + StartLocation;
	
	ECollisionChannel CollisionChannel = ECC_Visibility;
	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(this);
	
	GetWorld()->LineTraceSingleByChannel(OutHit, StartLocation, EndLocation, CollisionChannel, QueryParams);

	return OutHit;
}
#pragma endregion 