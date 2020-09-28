// Fill out your copyright notice in the Description page of Project Settings.


#include "BasePlayer.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "DrawDebugHelpers.h"
#include "Engine/Engine.h"
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

	//Interaction
	PlayerInputComponent->BindAction("Interact", IE_Pressed, this, &ABasePlayer::Interact);


	//Movement
	PlayerInputComponent->BindAxis("MoveForward", this, &ABasePlayer::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ABasePlayer::MoveRight);


	//Turning
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);


	//Switching weapon functions
	 //Should be changed to a BindAction or else it repeats
	PlayerInputComponent->BindAxis("WeaponSelectNum", this, &ABasePlayer::SwitchToInventorySlot);
	//This isn't working as I thought it would work
	PlayerInputComponent->BindAxis("WeaponSelectMouseWheel", this, &ABasePlayer::SwitchInventoryWithMouseWheel);

}


#define Use() ;// ->Use;
void ABasePlayer::UseWeapon()
{
	if (pActiveWeapon != nullptr)
	{
		//Use the weapon
		pActiveWeapon Use()
	}
}
#undef Use


#define pActiveWeaponGetMesh nullptr; 
void ABasePlayer::SetWeaponMesh()
{
	pWeaponMesh = pActiveWeaponGetMesh;
}
#undef pActiveWeaponGetMesh


#define InventoryGetItem(item) nullptr; print( "item selected");
//Switches to the specific slot in the inventory that was pressed
void ABasePlayer::SwitchToInventorySlot(float item)
{
	if (item == 0.0f) return;

	//Cast the item number to an int for the switch statement
	int val = static_cast<int>(item);

	switch (val)
	{
	case 1:
		//Select the Gun
		pActiveWeapon = InventoryGetItem(gun);
		break;
	case 2:
		//Select melee
		pActiveWeapon = InventoryGetItem(melee);
		break;
	case 3:
		//Select class item
		pActiveWeapon = InventoryGetItem(classItem);
		break;
	case 4:
		//Select Grenade
		pActiveWeapon = InventoryGetItem(grenade);
		break;
	default:
		print("Whoops we didn't switch to a valid item");
		break;
	}

	SetWeaponMesh();

}

void ABasePlayer::SwitchInventoryWithMouseWheel(float val)
{
	if (val == 0.0f) return;

	if (val < 0.0f) SwitchInventoryMouseWheelDown();
	else		 SwitchInventoryMouseWheelUp();

	SetWeaponMesh();

}

void ABasePlayer::SwitchInventoryMouseWheelUp()
{
	//Select next item in inventory
	InventoryGetItem(next);
}

void ABasePlayer::SwitchInventoryMouseWheelDown()
{
	//Select previous item in inventory
	InventoryGetItem(Previous);
}
#undef InventoryGetItem


void ABasePlayer::Interact()
{
	FHitResult ray;

	print("Interacting");

	if (pRaycastComponent->RaycastSingleFromPlayer(ray, 300.0f))
	{

		//Draw a Debug line while in the editor only
#if WITH_EDITOR
		DrawDebugLine(GetWorld(), ray.TraceStart, ray.TraceEnd, FColor::Cyan);
#endif

		AActor *hitObj = ray.GetActor();
		if (hitObj != nullptr)
		{
			if (hitObj->Tags.Contains("System"))
			{
				//We hit a repairable object if Robert has named this the same
				Repair(hitObj);
			}
		}


	}
}

// Called when the game starts or when spawned
void ABasePlayer::BeginPlay()
{
	Super::BeginPlay();

	//A Function to add the tag automatically in case I forget
	AddPlayerTags();


	//Populate the inventory everytime BeginPlay gets called
	bHasPopulatedInventory = false;
	PopulateInventory();
	
}


//A DEMO CLASS THAT WILL BE REMOVED BEFORE MONDAY
class RepairObjectDemoByNick
{
public:
	int GetType() { return rand() % 3; }
	void Repair(float f) { }
};

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
			if (hitObj->Tags.Contains("System"))
			{
				//We hit a repairable object if Robert has named this the same
				Repair(hitObj);
			}
		}
	}
}

void ABasePlayer::Repair(AActor *repairObj)
{

	RepairObjectDemoByNick* repairObject = nullptr; // Cast<RepairObjectDemoByNick*>(repairObj);
	if (repairObject == nullptr) return;

	switch (repairObject->GetType())
	{
	case 0:
		print("Engineer Repair");
		repairObject->Repair(classInformation.fEngineeringRepairSpeed);
		break;

	case 1:
		print("Medic Repair?");
		repairObject->Repair(classInformation.fMedicRepairSpeed);
		break;

	case 2:
		print("Common Repair?");
		repairObject->Repair(classInformation.fCommonRepairSpeed);
		break;

	default:
		print("Deafult Repair?");
		repairObject->Repair(classInformation.fDefaultRepairSpeed);
		break;
	}
}

// Called every frame
void ABasePlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

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


void ABasePlayer::ClassSpecialty()
{
	print("This is the Base Class function which is incomplete");
}


//I am not sure how the inventory is going to work
//Putting this here to quickly and easily change it all at once
#define AddToInventory(item); ;

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


	if (classInformation.gunItemTemplate != nullptr)
	{
		//Create the GunItem
		AWeapon* gun = world->SpawnActor<AWeapon>(classInformation.gunItemTemplate, spawnParams);

		//Add it to inventory
		AddToInventory(gun);
		//pInventoryComponent->AddItem(gun);
		//pInventoryComponent->pGunItem = gun;
	}
	else
	{
		print("No Gun Item");
	}


	if (classInformation.meleeItemTemplate != nullptr)
	{
		//Create the Melee item
		AWeapon* melee = world->SpawnActor<AWeapon>(classInformation.meleeItemTemplate, spawnParams);

		//Add it to inventory
		AddToInventory(melee);
		//pInventoryComponent->AddItem(melee);
		//pInventoryComponent->pMeleeItem = melee;
	}
	else
	{
		print("No Melee Item");
	}


	if (classInformation.classItemTemplate != nullptr)
	{
		//Create the Class item
		AWeapon* classItem = world->SpawnActor<AWeapon>(classInformation.classItemTemplate, spawnParams);

		//Add it to inventory
		AddToInventory(classItem);
		//pInventoryComponent->AddItem(classItem);
		//pInventoryComponent->pClassItem = classItem;
	}
	else
	{
		print("No class Item");
	}


	if (classInformation.grenadeItemTemplate != nullptr)
	{
		//Create the Class item
		AWeapon* grenade = world->SpawnActor<AWeapon>(classInformation.grenadeItemTemplate, spawnParams);

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


#undef print