// Fill out your copyright notice in the Description page of Project Settings.


#include "BasePlayer.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "DrawDebugHelpers.h"
#include "Engine/Engine.h"
#include "EventObject.h"
#include "HealthComponent.h"
#include "RaycastComponent.h"
#include "UInventory.h"
#include "Weapon.h"


#undef print
#define print(msg) GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Red, msg);

// Sets default values
ABasePlayer::ABasePlayer()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Setup Collider
	GetCapsuleComponent()->InitCapsuleSize(55.f, 96.0f);

	//Setup Camera
	pCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	pCameraComponent->SetupAttachment(GetCapsuleComponent());
	pCameraComponent->SetRelativeLocation(FVector(-39.56f, 1.75f, 64.f)); // Position the camera
	pCameraComponent->bUsePawnControlRotation = true;

	//Setup Mesh
	pMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Player Mesh"));
	pMeshComponent->SetOnlyOwnerSee(true);
	pMeshComponent->SetupAttachment(pCameraComponent);
	pMeshComponent->bCastDynamicShadow = false;
	pMeshComponent->CastShadow = false;
	pMeshComponent->SetRelativeRotation(FRotator(1.9f, -19.19f, 5.2f));
	pMeshComponent->SetRelativeLocation(FVector(-0.5f, -4.4f, -155.7f));

	// Create a gun mesh component
	pWeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Weapon Mesh"));
	pWeaponMesh->SetOnlyOwnerSee(true);			// only the owning player will see this mesh
	pWeaponMesh->bCastDynamicShadow = false;
	pWeaponMesh->CastShadow = false;
	pWeaponMesh->SetupAttachment(RootComponent);


	//Setup the Health Component
	pHealthComponent = CreateDefaultSubobject<UHealthComponent>("Health Component");


	//Setup the Inventory Component
	pInventoryComponent = CreateDefaultSubobject<UUInventory>("Inventory Component");


	//Setup the Raycast Component
	pRaycastComponent = CreateDefaultSubobject<URaycastComponent>("Raycast Component");

}


// Called when the game starts or when spawned
void ABasePlayer::BeginPlay()
{
	Super::BeginPlay();

	//They are binding the Gun here in the Prototype
	pWeaponMesh->AttachToComponent(pMeshComponent, FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true), TEXT("GripPoint"));

	//A Function to add the tag automatically in case I forget
	AddPlayerTags();


	//Populate the inventory everytime BeginPlay gets called
	bHasPopulatedInventory = false;
	PopulateInventory();
}


// Called every frame
void ABasePlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);



}


void ABasePlayer::ClassSpecialty()
{
	print("This is the Base Class function which is incomplete");
}


void ABasePlayer::ReplenishHealth()
{
	//HealthComponent Regain Health
	//Base on the players Regen Speed

	//pHealthComponent->Heal();
}

// Called to bind functionality to input
void ABasePlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Bind jump events
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	//Our main action event
	// Bind fire event
	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &ABasePlayer::UseWeapon);
	PlayerInputComponent->BindAction("Fire", IE_Released, this, &ABasePlayer::StopUsingWeapon);

	//Interaction
	PlayerInputComponent->BindAction("Interact", IE_Pressed, this, &ABasePlayer::Interact);
	PlayerInputComponent->BindAction("ClassSpecialty", IE_Pressed, this, &ABasePlayer::ClassSpecialty);

	//Movement
	PlayerInputComponent->BindAxis("MoveForward", this, &ABasePlayer::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ABasePlayer::MoveRight);


	//Turning
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);


	//Switching weapon functions
	//Individual Number presses
	PlayerInputComponent->BindAction("WeaponSelectNum1", IE_Pressed, this, &ABasePlayer::SwitchToItemOne);
	PlayerInputComponent->BindAction("WeaponSelectNum2", IE_Pressed, this, &ABasePlayer::SwitchToItemTwo);
	PlayerInputComponent->BindAction("WeaponSelectNum3", IE_Pressed, this, &ABasePlayer::SwitchToItemThree);
	PlayerInputComponent->BindAction("WeaponSelectNum4", IE_Pressed, this, &ABasePlayer::SwitchToItemFour);

	//This isn't working as I thought it would work
	PlayerInputComponent->BindAction("WeaponSelectMouseWheelUp",   IE_Pressed, this, &ABasePlayer::SwitchInventoryMouseWheelUp  );
	PlayerInputComponent->BindAction("WeaponSelectMouseWheelDown", IE_Pressed, this, &ABasePlayer::SwitchInventoryMouseWheelDown);

}


void ABasePlayer::UseWeapon()
{
	if (pActiveWeapon != nullptr)
	{
		//Use the weapon
		pActiveWeapon->Use();
	}
	else
	{
		print("Active weapon was null while trying to use");
	}
}

void ABasePlayer::StopUsingWeapon()
{
	//pActiveWeapon->StopFire();
}


void ABasePlayer::SwitchToItemOne()
{
	print("Switch to item with 1");
	SwitchToInventorySlot(1);
}

void ABasePlayer::SwitchToItemTwo()
{
	print("Switch to item with 2");
	SwitchToInventorySlot(2);
}

void ABasePlayer::SwitchToItemThree()
{
	print("Switch to item with 3");
	SwitchToInventorySlot(3);
}

void ABasePlayer::SwitchToItemFour()
{
	print("Switch to item with 4");
	SwitchToInventorySlot(4);
}

#define InventoryGetItem(item) nullptr; // Cast<AWeapon>(pInventoryComponent->GetItem(item));
//Switches to the specific slot in the inventory that was pressed
void ABasePlayer::SwitchToInventorySlot(int val)
{
	switch (val)
	{
	case 1:
		//Select the Gun
		pActiveWeapon = InventoryGetItem(val - 1);
		print("Selected Item: Gun ");
		break;
	case 2:
		//Select melee
		pActiveWeapon = InventoryGetItem(val - 1);
		print("Selected Item: Melee ");
		break;
	case 3:
		//Select class item
		pActiveWeapon = InventoryGetItem(val - 1);
		print("Selected Item: Class Item ");
		break;
	case 4:
		//Select Grenade
		pActiveWeapon = InventoryGetItem(val - 1);
		print("Selected Item: Grenade");
		break;
	default:
		print("Whoops we didn't switch to a valid item");
		break;
	}

	SetWeaponMesh();

}


void ABasePlayer::SwitchInventoryMouseWheelUp()
{
	//Select next item in inventory
	pActiveWeapon = nullptr; // Cast<AWeapon>(pInventoryComponent->GetNext());
	print("Mouse wheel UP select");
	SetWeaponMesh();
}

void ABasePlayer::SwitchInventoryMouseWheelDown()
{
	//Select previous item in inventory
	pActiveWeapon = nullptr; // Cast<AWeapon>(pInventoryComponent->GetPrev());
	print("Mouse wheel DOWN select");
	SetWeaponMesh();
}
#undef InventoryGetItem


void ABasePlayer::Interact()
{
	FHitResult ray;

	print("Interact function entered");

	if (pRaycastComponent->RaycastSingleFromPlayer(ray, 300.0f))
	{
		//Draw a Debug line while in the editor only
		#if WITH_EDITOR
		DrawDebugLine(GetWorld(), ray.TraceStart, ray.TraceEnd, FColor::Cyan);
		#endif

		AActor *hitObj = ray.GetActor();
		if (hitObj != nullptr)
		{
			if (hitObj->Tags.Contains("SystemEvent"))
			{
				//We hit a repairable object if Robert has named this the same
				Repair(hitObj);
			}
		}
	}
}


void ABasePlayer::Repair()
{
	//Just raycast to see if the actor in front of us is repairable
	//Then we take that object and pass it into another function
	//Interact();
	FHitResult ray;

	print("Repairing function");

	if (pRaycastComponent->RaycastSingleFromPlayer(ray, 300.0f))
	{
		//Draw a Debug line while in the editor only
		#if WITH_EDITOR
		DrawDebugLine(GetWorld(), ray.TraceStart, ray.TraceEnd, FColor::Red);
		#endif

		AActor* hitObj = ray.GetActor();
		if (hitObj != nullptr)
		{
			if (hitObj->Tags.Contains("SystemEvent"))
			{
				//We hit a repairable object if Robert has named this the same
				Repair(hitObj);
			}
		}
	}
}

void ABasePlayer::Repair(AActor *repairObj)
{
	AEventObject* repairObject =  Cast<AEventObject>(repairObj);

	if (repairObject == nullptr)
	{
		print("Repiar object was null");
		return;
	}

	if (repairObject->IsActive())
	{
		print("Repairing the object");
		repairObject->Deactivate();
	}
}


void ABasePlayer::OnInteract()
{

	onPlayerInteract.Broadcast(this);

}

void ABasePlayer::MoveRight(float val)
{
	if (val != 0.0f)
	{
		AddMovementInput(GetActorRightVector(), val);
	}
}
void ABasePlayer::MoveForward(float val)
{
	if (val != 0.0f)
	{
		AddMovementInput(GetActorForwardVector(), val);
	}
}


//I am not sure how the inventory is going to work
//Putting this here to quickly and easily change it all at once
#define AddToInventory(item); pInventoryComponent->AddItemToInventory(item);

void ABasePlayer::PopulateInventory()
{
	//GEngine->AddOnScreenDebugMessage(0, 3, FColor::Red, "Populate Inventory called & incomplete");
	print("Populate Inventory called and incomplete");

	if (bHasPopulatedInventory)
	{
		return; //We don't want to repopulate the inventory more than once do we?
	}


	UWorld* world = GetWorld();	//Get the world
	FActorSpawnParameters spawnParams;	//Just basic spawnParams


	if (classInformation.weaponInformation.gunItemTemplate != nullptr)
	{
		//Create the GunItem
		AWeapon* gun = world->SpawnActor<AWeapon>(classInformation.weaponInformation.gunItemTemplate, spawnParams);

		//Add it to inventory
		AddToInventory(gun);
		//pInventoryComponent->AddItem(gun);
		//pInventoryComponent->pGunItem = gun;
	}
	else
	{
		print("No Gun Item");
	}


	if (classInformation.weaponInformation.meleeItemTemplate != nullptr)
	{
		//Create the Melee item
		AWeapon* melee = world->SpawnActor<AWeapon>(classInformation.weaponInformation.meleeItemTemplate, spawnParams);

		//Add it to inventory
		AddToInventory(melee);
		//pInventoryComponent->AddItem(melee);
		//pInventoryComponent->pMeleeItem = melee;
	}
	else
	{
		print("No Melee Item");
	}


	if (classInformation.weaponInformation.classItemTemplate != nullptr)
	{
		//Create the Class item
		AWeapon* classItem = world->SpawnActor<AWeapon>(classInformation.weaponInformation.classItemTemplate, spawnParams);

		//Add it to inventory
		AddToInventory(classItem);
		//pInventoryComponent->AddItem(classItem);
		//pInventoryComponent->pClassItem = classItem;
	}
	else
	{
		print("No class Item");
	}


	if (classInformation.weaponInformation.grenadeItemTemplate != nullptr)
	{
		//Create the Class item
		AWeapon* grenade = world->SpawnActor<AWeapon>(classInformation.weaponInformation.grenadeItemTemplate, spawnParams);

		//Add it to inventory
		AddToInventory(grenade);
		//pInventoryComponent->AddItem(grenade);
		//pInventoryComponent->pGrenadeItem = grenade;
	}
	else
	{
		print("No grenade Item");
	}


	//We have populated the inventory
	bHasPopulatedInventory = true;
}
#undef AddToInventory


void ABasePlayer::AddPlayerTags()
{
	//Add the item tags in case I forgot to add them in code
	switch (classInformation.playerClass)
	{
	case PlayerClass::Unknown : 
		print("The tag being added was not set or Unknown");
		break;

	case PlayerClass::Engineer :
		if (!ActorHasTag("Engineer"))
		{
			this->Tags.Add("Engineer");
		}
		break;

	case PlayerClass::Medic :
		if (!ActorHasTag("Medic"))
		{
			this->Tags.Add("Medic");
		}
		break;

	case PlayerClass::Gunner :
		if (!ActorHasTag("Gunner"))
		{
			this->Tags.Add("Gunner");
		}
		break;

	default :
		print("The tag being added was not set or Base");
		break;
	}
}


void ABasePlayer::SetWeaponMesh()
{
	//pWeaponMesh = pActiveWeapon->GetMesh();
}


#undef print