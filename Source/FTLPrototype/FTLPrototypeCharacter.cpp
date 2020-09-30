// Copyright Epic Games, Inc. All Rights Reserved.

#include "FTLPrototypeCharacter.h"
#include "FTLPrototypeProjectile.h"
#include "Animation/AnimInstance.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/InputSettings.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "MotionControllerComponent.h"
#include "XRMotionControllerBase.h" // for FXRMotionControllerBase::RightHandSourceId
#include "DrawDebugHelpers.h"
#include "Public/EventObject.h"
#include "Weapon.h"
#include "UInventory.h"
#include "JustinFolder/FTLPrototypeHealthComponent.h"
#include "GameFramework/PawnMovementComponent.h"
#include "GameFramework/Actor.h"

#include "RaycastComponent.h"

DEFINE_LOG_CATEGORY_STATIC(LogFPChar, Warning, All);

//////////////////////////////////////////////////////////////////////////
// AFTLPrototypeCharacter

AFTLPrototypeCharacter::AFTLPrototypeCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(55.f, 96.0f);

	// set our turn rates for input
	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;

	// Create a CameraComponent	
	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCameraComponent->SetupAttachment(GetCapsuleComponent());
	FirstPersonCameraComponent->SetRelativeLocation(FVector(-39.56f, 1.75f, 64.f)); // Position the camera
	FirstPersonCameraComponent->bUsePawnControlRotation = true;

	// Create a mesh component that will be used when being viewed from a '1st person' view (when controlling this pawn)
	Mesh1P = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("CharacterMesh1P"));
	Mesh1P->SetOnlyOwnerSee(true);
	Mesh1P->SetupAttachment(FirstPersonCameraComponent);
	Mesh1P->bCastDynamicShadow = false;
	Mesh1P->CastShadow = false;
	Mesh1P->SetRelativeRotation(FRotator(1.9f, -19.19f, 5.2f));
	Mesh1P->SetRelativeLocation(FVector(-0.5f, -4.4f, -155.7f));

	// Create a gun mesh component
	FP_Gun = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("FP_Gun"));
	FP_Gun->SetOnlyOwnerSee(true);			// only the owning player will see this mesh
	FP_Gun->bCastDynamicShadow = false;
	FP_Gun->CastShadow = false;
	// FP_Gun->SetupAttachment(Mesh1P, TEXT("GripPoint"));
	FP_Gun->SetupAttachment(RootComponent);

	FP_MuzzleLocation = CreateDefaultSubobject<USceneComponent>(TEXT("MuzzleLocation"));
	FP_MuzzleLocation->SetupAttachment(FP_Gun);
	FP_MuzzleLocation->SetRelativeLocation(FVector(0.2f, 48.4f, -10.6f));

	// Default offset from the character location for projectiles to spawn
	GunOffset = FVector(100.0f, 0.0f, 10.0f);

	// Note: The ProjectileClass and the skeletal mesh/anim blueprints for Mesh1P, FP_Gun, and VR_Gun 
	// are set in the derived blueprint asset named MyCharacter to avoid direct content references in C++.

	// Create VR Controllers.
	R_MotionController = CreateDefaultSubobject<UMotionControllerComponent>(TEXT("R_MotionController"));
	R_MotionController->MotionSource = FXRMotionControllerBase::RightHandSourceId;
	R_MotionController->SetupAttachment(RootComponent);
	L_MotionController = CreateDefaultSubobject<UMotionControllerComponent>(TEXT("L_MotionController"));
	L_MotionController->SetupAttachment(RootComponent);

	// Create a gun and attach it to the right-hand VR controller.
	// Create a gun mesh component
	VR_Gun = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("VR_Gun"));
	VR_Gun->SetOnlyOwnerSee(true);			// only the owning player will see this mesh
	VR_Gun->bCastDynamicShadow = false;
	VR_Gun->CastShadow = false;
	VR_Gun->SetupAttachment(R_MotionController);
	VR_Gun->SetRelativeRotation(FRotator(0.0f, -90.0f, 0.0f));

	VR_MuzzleLocation = CreateDefaultSubobject<USceneComponent>(TEXT("VR_MuzzleLocation"));
	VR_MuzzleLocation->SetupAttachment(VR_Gun);
	VR_MuzzleLocation->SetRelativeLocation(FVector(0.000004, 53.999992, 10.000000));
	VR_MuzzleLocation->SetRelativeRotation(FRotator(0.0f, 90.0f, 0.0f));		// Counteract the rotation of the VR gun model.

	pRaycastComponent = CreateDefaultSubobject<URaycastComponent>(TEXT("RaycastComponent"));

	HealthComp = CreateDefaultSubobject<UFTLPrototypeHealthComponent>(TEXT("HealthComp"));

	bDied = false;

	// Uncomment the following line to turn motion controllers on by default:
	//bUsingMotionControllers = true;

	//Setup the Inventory Component
	pInventoryComponent = CreateDefaultSubobject<UUInventory>("Inventory Component");
}

void AFTLPrototypeCharacter::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();

	//Attach gun mesh component to Skeleton, doing it here because the skeleton is not yet created in the constructor
	FP_Gun->AttachToComponent(Mesh1P, FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true), TEXT("GripPoint"));

	// Show or hide the two versions of the gun based on whether or not we're using motion controllers.
	if (bUsingMotionControllers)
	{
		VR_Gun->SetHiddenInGame(false, true);
		Mesh1P->SetHiddenInGame(true, true);
	}
	else
	{
		VR_Gun->SetHiddenInGame(true, true);
		Mesh1P->SetHiddenInGame(false, true);

	}

	PopulateInventory();
	
	HealthComp->OnHealthChanged.AddDynamic(this, &AFTLPrototypeCharacter::OnHealthChanged);


}

void AFTLPrototypeCharacter::OnInteract()
{
	TArray<FHitResult> rays;
	if (pRaycastComponent->RaycastMultiFromPlayer(rays, 2000.f))
	{
		for (auto& ray : rays)
		{
			if (ray.GetActor()->ActorHasTag("SystemEvent"))
			{
				AEventObject* pEventObject = Cast<AEventObject>(ray.GetActor());
				if (pEventObject)
				{
					if (pEventObject->IsActive())
					{
						pEventObject->Deactivate();
					}
				}
				//ray.GetActor()->SetActorLocation(ray.GetActor()->GetActorLocation() + FVector::UpVector * 150.0f);
			}
		}
		//if (ray.GetActor()->Tags.Contains("White"))
		//	ray.GetActor()->SetActorLocation(ray.GetActor()->GetActorLocation() + FVector::UpVector * 20);
		//else if (ray.GetActor()->Tags.Contains("Gold"))
		//	ray.GetActor()->SetActorLocation(ray.GetActor()->GetActorLocation() + FVector::UpVector * 75);
	}
}

//////////////////////////////////////////////////////////////////////////
// Input

void AFTLPrototypeCharacter::PopulateInventory()
{
	if (bHasPopulatedInventory)
	{
		return; //We don't want to repopulate the inventory more than once do we?
	}


	UWorld* world = GetWorld();	//Get the world
	FActorSpawnParameters spawnParams;	//Just basic spawnParams


	if (classInformation.gunItemTemplate != nullptr)
	{
		//Create the GunItem
		AWeapon* gun = world->SpawnActor<AWeapon>(classInformation.gunItemTemplate, spawnParams);

		//Add it to inventory
		pInventoryComponent->GunItem = gun;
		//pInventoryComponent->AddItem(gun);
		//pInventoryComponent->pGunItem = gun;
	}
	else
	{
		//print("No Gun Item");
	}


	if (classInformation.meleeItemTemplate != nullptr)
	{
		//Create the Melee item
		AWeapon* melee = world->SpawnActor<AWeapon>(classInformation.meleeItemTemplate, spawnParams);

		//Add it to inventory
		pInventoryComponent->MeleeItem = melee;
		//pInventoryComponent->AddItem(melee);
		//pInventoryComponent->pMeleeItem = melee;
	}
	else
	{
		//print("No Melee Item");
	}


	if (classInformation.classItemTemplate != nullptr)
	{
		//Create the Class item
		AWeapon* classItem = world->SpawnActor<AWeapon>(classInformation.classItemTemplate, spawnParams);

		//Add it to inventory
		pInventoryComponent->ClassItem = classItem;
		//pInventoryComponent->AddItem(classItem);
		//pInventoryComponent->pClassItem = classItem;
	}
	else
	{
		//	print("No class Item");
	}


	if (classInformation.grenadeItemTemplate != nullptr)
	{
		//Create the Class item
		AWeapon* grenade = world->SpawnActor<AWeapon>(classInformation.grenadeItemTemplate, spawnParams);

		//Add it to inventory
		pInventoryComponent->GrenadeItemClass = grenade;
		//pInventoryComponent->AddItem(grenade);
		//pInventoryComponent->pGrenadeItem = grenade;
	}
	else
	{
		//	print("No grenade Item");
	}


	//We have populated the inventory
	bHasPopulatedInventory = true;
}

void AFTLPrototypeCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// set up gameplay key bindings
	check(PlayerInputComponent);

	// Bind jump events
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);
	PlayerInputComponent->BindAction("Interact", IE_Pressed, this, &AFTLPrototypeCharacter::OnInteract);

	// Bind fire event
	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &AFTLPrototypeCharacter::OnFire);

	// Bind reload event
	//PlayerInputComponent->BindAction("Reload", IE_Pressed, this, &AFTLPrototypeCharacter::Reload);

	// Enable touchscreen input
	EnableTouchscreenMovement(PlayerInputComponent);

	PlayerInputComponent->BindAction("ResetVR", IE_Pressed, this, &AFTLPrototypeCharacter::OnResetVR);

	// Bind movement events
	PlayerInputComponent->BindAxis("MoveForward", this, &AFTLPrototypeCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AFTLPrototypeCharacter::MoveRight);

	// We have 2 versions of the rotation bindings to handle different kinds of devices differently
	// "turn" handles devices that provide an absolute delta, such as a mouse.
	// "turnrate" is for devices that we choose to treat as a rate of change, such as an analog joystick
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("TurnRate", this, &AFTLPrototypeCharacter::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("LookUpRate", this, &AFTLPrototypeCharacter::LookUpAtRate);

	PlayerInputComponent->BindAxis("WeaponSelectNum", this, &AFTLPrototypeCharacter::SwitchToInventorySlot);
	//This isn't working as I thought it would work
	PlayerInputComponent->BindAxis("WeaponSelectMouseWheel", this, &AFTLPrototypeCharacter::SwitchInventoryWithMouseWheel);
}

void AFTLPrototypeCharacter::OnFire()
{
	// try and fire a projectile

	//if (ProjectileClass != NULL)
	//{
	//	UWorld* const World = GetWorld();
	//	if (World != NULL)
	//	{
	//		if (bUsingMotionControllers)
	//		{
	//			const FRotator SpawnRotation = VR_MuzzleLocation->GetComponentRotation();
	//			const FVector SpawnLocation = VR_MuzzleLocation->GetComponentLocation();
	//			World->SpawnActor<AFTLPrototypeProjectile>(ProjectileClass, SpawnLocation, SpawnRotation);
	//		}
	//		else
	//		{
	//			const FRotator SpawnRotation = GetControlRotation();
	//			// MuzzleOffset is in camera space, so transform it to world space before offsetting from the character location to find the final muzzle position
	//			const FVector SpawnLocation = ((FP_MuzzleLocation != nullptr) ? FP_MuzzleLocation->GetComponentLocation() : GetActorLocation()) + SpawnRotation.RotateVector(GunOffset);
	//
	//			//Set Spawn Collision Handling Override
	//			FActorSpawnParameters ActorSpawnParams;
	//			ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;
	//
	//			// spawn the projectile at the muzzle
	//			World->SpawnActor<AFTLPrototypeProjectile>(ProjectileClass, SpawnLocation, SpawnRotation, ActorSpawnParams);
	//		}
	//	}
	//}

	//Call FireStart() on current weapon
	// try and play the sound if specified
	if (FireSound != NULL)
	{
		UGameplayStatics::PlaySoundAtLocation(this, FireSound, GetActorLocation());
	}

	// try and play a firing animation if specified
	if (FireAnimation != NULL)
	{
		// Get the animation object for the arms mesh
		UAnimInstance* AnimInstance = Mesh1P->GetAnimInstance();
		if (AnimInstance != NULL)
		{
			AnimInstance->Montage_Play(FireAnimation, 1.f);
		}
	}
}

void AFTLPrototypeCharacter::Reload()
{
	//Call ReloadStart() on current weapon
}

void AFTLPrototypeCharacter::OnResetVR()
{
	UHeadMountedDisplayFunctionLibrary::ResetOrientationAndPosition();
}

void AFTLPrototypeCharacter::BeginTouch(const ETouchIndex::Type FingerIndex, const FVector Location)
{
	if (TouchItem.bIsPressed == true)
	{
		return;
	}
	if ((FingerIndex == TouchItem.FingerIndex) && (TouchItem.bMoved == false))
	{
		OnFire();
	}
	TouchItem.bIsPressed = true;
	TouchItem.FingerIndex = FingerIndex;
	TouchItem.Location = Location;
	TouchItem.bMoved = false;
}

void AFTLPrototypeCharacter::EndTouch(const ETouchIndex::Type FingerIndex, const FVector Location)
{
	if (TouchItem.bIsPressed == false)
	{
		return;
	}
	TouchItem.bIsPressed = false;
}

//Commenting this section out to be consistent with FPS BP template.
//This allows the user to turn without using the right virtual joystick

//void AFTLPrototypeCharacter::TouchUpdate(const ETouchIndex::Type FingerIndex, const FVector Location)
//{
//	if ((TouchItem.bIsPressed == true) && (TouchItem.FingerIndex == FingerIndex))
//	{
//		if (TouchItem.bIsPressed)
//		{
//			if (GetWorld() != nullptr)
//			{
//				UGameViewportClient* ViewportClient = GetWorld()->GetGameViewport();
//				if (ViewportClient != nullptr)
//				{
//					FVector MoveDelta = Location - TouchItem.Location;
//					FVector2D ScreenSize;
//					ViewportClient->GetViewportSize(ScreenSize);
//					FVector2D ScaledDelta = FVector2D(MoveDelta.X, MoveDelta.Y) / ScreenSize;
//					if (FMath::Abs(ScaledDelta.X) >= 4.0 / ScreenSize.X)
//					{
//						TouchItem.bMoved = true;
//						float Value = ScaledDelta.X * BaseTurnRate;
//						AddControllerYawInput(Value);
//					}
//					if (FMath::Abs(ScaledDelta.Y) >= 4.0 / ScreenSize.Y)
//					{
//						TouchItem.bMoved = true;
//						float Value = ScaledDelta.Y * BaseTurnRate;
//						AddControllerPitchInput(Value);
//					}
//					TouchItem.Location = Location;
//				}
//				TouchItem.Location = Location;
//			}
//		}
//	}
//}

void AFTLPrototypeCharacter::MoveForward(float Value)
{
	if (Value != 0.0f)
	{
		// add movement in that direction
		AddMovementInput(GetActorForwardVector(), Value);
	}
}

void AFTLPrototypeCharacter::MoveRight(float Value)
{
	if (Value != 0.0f)
	{
		// add movement in that direction
		AddMovementInput(GetActorRightVector(), Value);
	}
}

void AFTLPrototypeCharacter::TurnAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void AFTLPrototypeCharacter::LookUpAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}

bool AFTLPrototypeCharacter::EnableTouchscreenMovement(class UInputComponent* PlayerInputComponent)
{
	if (FPlatformMisc::SupportsTouchInput() || GetDefault<UInputSettings>()->bUseMouseForTouch)
	{
		PlayerInputComponent->BindTouch(EInputEvent::IE_Pressed, this, &AFTLPrototypeCharacter::BeginTouch);
		PlayerInputComponent->BindTouch(EInputEvent::IE_Released, this, &AFTLPrototypeCharacter::EndTouch);

		//Commenting this out to be more consistent with FPS BP template.
		//PlayerInputComponent->BindTouch(EInputEvent::IE_Repeat, this, &AFTLPrototypeCharacter::TouchUpdate);
		return true;
	}
	
	return false;
}


void AFTLPrototypeCharacter::SetWeaponMesh()
{
	FP_Gun.me = pActiveWeapon->GetMesh();
}

void AFTLPrototypeCharacter::SwitchToInventorySlot(float item)
{
	if (item == 0.0f) return;

	//Cast the item number to an int for the switch statement
	int val = static_cast<int>(item);

	switch (val)
	{
	case 1:
		//Select the Gun
		pActiveWeapon = pInventoryComponent->GunItem;
		weaponat = item;
		break;
	case 2:
		//Select melee
		pActiveWeapon = pInventoryComponent->MeleeItem;
		weaponat = item;
		break;
	case 3:
		//Select class item
		pActiveWeapon = pInventoryComponent->ClassItem;
		weaponat = item;
		break;
	case 4:
		//Select Grenade
		pActiveWeapon = pInventoryComponent->GrenadeItemClass;
		weaponat = item;
		break;
	default:
		//print("Whoops we didn't switch to a valid item");
		break;
	}

	SetWeaponMesh();
}

void AFTLPrototypeCharacter::SwitchInventoryWithMouseWheel(float val)
{
}

void AFTLPrototypeCharacter::SwitchInventoryMouseWheelUp()
{
}

void AFTLPrototypeCharacter::SwitchInventoryMouseWheelDown()
{
	
void AFTLPrototypeCharacter::OnHealthChanged(UFTLPrototypeHealthComponent* InHealthComp, float Health, float HealthDelta, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser)
{
	GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Green, "Player's Health: " + FString::SanitizeFloat(Health));
	if (Health <= 0 && !bDied)
	{
		bDied = true;

		GetMovementComponent()->StopMovementImmediately();
		GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		GetMesh()->SetVisibility(false);

		DetachFromControllerPendingDestroy();
		SetLifeSpan(10.0f);
	}
	
}
