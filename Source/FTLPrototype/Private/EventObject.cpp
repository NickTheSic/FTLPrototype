// Fill out your copyright notice in the Description page of Project Settings.


#include "EventObject.h"
#include "InteractableBox.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "Materials/Material.h"
#include "BasePlayer.h"
#include "../FTLPrototypeCharacter.h"
#include "../JustinFolder/FTLPrototypeHealthComponent.h"
#include "EngineUtils.h"
#include "SpawnPoint.h"
#include "../JustinFolder/FTLPrototypeAI.h"

// Sets default values
AEventObject::AEventObject()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	pBoxCollider = CreateDefaultSubobject<UBoxComponent>("BoxCollider");
	pBoxCollider->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	pBoxCollider->SetSimulatePhysics(true);
	RootComponent = pBoxCollider;

	pStaticMesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	pStaticMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	pStaticMesh->SetupAttachment(RootComponent);

	//Material meshs for on/off states
	pActiveMaterial = CreateDefaultSubobject<UMaterial>("ActiveMaterial");
	pDeactiveMaterial = CreateDefaultSubobject<UMaterial>("DeactiveMaterial");

	Tags.Add("SystemEvent");

	bisActive = false;
	pPlayer = nullptr;

	SpawnPos1 = FVector::ZeroVector;
	SpawnPos2 = FVector::ZeroVector;
}

// Called when the game starts or when spawned
void AEventObject::BeginPlay()
{
	Super::BeginPlay();

	//Looking for the active player, only good for prototype
	for (TActorIterator<AFTLPrototypeCharacter> ActorItr(GetWorld()); ActorItr; ++ActorItr)
	{
		if (ActorItr)
		{
			pPlayer = Cast<AFTLPrototypeCharacter>(*ActorItr);
		}
	}

	//Works as a basic Init function and sets up the event to not be active
	Deactivate();

}

// Called every frame
void AEventObject::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	
}

void AEventObject::Activate()
{
	//Changes the Mesh and sets the bool to true
	bisActive = true;
	pStaticMesh->SetMaterial(0, pActiveMaterial);

	//All events can activate any ammount of timers below and will only be call by variables already set in blueprints.
	if (bHealthEvent)
	{
		GetWorld()->GetTimerManager().SetTimer(HealthDecrementTimer, this, &AEventObject::LowerHealth, fHealthEventSpeed, true);
	}

	if (bOxygenEvent)
	{
		GetWorld()->GetTimerManager().SetTimer(OxygenDecrementTimer, this, &AEventObject::LowerOxygen, fOxygenEventSpeed, true);
	}

	if (bSpawnEvent)
	{
		SpawnEnemy();
		GetWorld()->GetTimerManager().SetTimer(SpawnTimer, this, &AEventObject::SpawnEnemy, fSpawnEventSpeed, true);
	}

}

void AEventObject::Deactivate()
{
	//Disables everything and sets the mesh back to a fixed state
	bisActive = false;
	pStaticMesh->SetMaterial(0, pDeactiveMaterial);

	//Clearing all timers so they dont activate again
	GetWorld()->GetTimerManager().ClearTimer(HealthDecrementTimer);
	GetWorld()->GetTimerManager().ClearTimer(OxygenDecrementTimer);
	GetWorld()->GetTimerManager().ClearTimer(SpawnTimer);

	//A Check and restoring all health/oxygen lost during the event when it was active
	if (fHealthLost > 0.0f)
	{
		float fRestoreHealth = fHealthCurrent + fHealthLost;
		if (fRestoreHealth > 100.0f)
		{
			fRestoreHealth = 100.0f;
		}
		pPlayer->GetHealthComponent()->SetHealth(fRestoreHealth);
	}

	if (fOxygenLost > 0.0f)
	{
		float fRestoreOxygen = fOxygenLost + fOxygenCurrent;
		if (fRestoreOxygen > 100.0f)
		{
			fRestoreOxygen = 100.0f;
		}
		pPlayer->GetHealthComponent()->SetOxygen(fRestoreOxygen);
	}

	//Clearing all values used in the event systems
	fHealthCurrent = 0.0f;
	fHealthLost = 0.0f;
	fOxygenCurrent = 0.0f;
	fOxygenLost = 0.0f;

	//Temporary for prototype, will randomly activate from a set value if no value set in blueprints
	if (fEventTimer > 0.0f)
	{
		GetWorld()->GetTimerManager().SetTimer(ActivationTimer, this, &AEventObject::Activate, fEventTimer, false);
	}
	else
	{ 
		float fRandomActivation = FMath::RandRange(5.0f, 20.0f);
		GetWorld()->GetTimerManager().SetTimer(ActivationTimer, this, &AEventObject::Activate, fRandomActivation, false);
	}
}

void AEventObject::LowerHealth()
{
	//Ticking the health down by 1 so speed determines how fast, and storing the amount lost during the event
	fHealthCurrent = pPlayer->GetHealthComponent()->GetHealth();
	fHealthCurrent -= fHealthEventValue;
	fHealthLost += fHealthEventValue;
	pPlayer->GetHealthComponent()->SetHealth(fHealthCurrent);
}

void AEventObject::LowerOxygen()
{
	//Ticking the oxygen down by 1 so speed determines how fast, and storing the amount lost during the event
	fOxygenCurrent = pPlayer->GetHealthComponent()->GetOxygen();
	fOxygenCurrent -= fOxygenEventValue;
	fOxygenLost += fOxygenEventValue;
	pPlayer->GetHealthComponent()->SetOxygen(fOxygenCurrent);
}

void AEventObject::SpawnEnemy()
{
	for (TActorIterator<ASpawnPoint> ActorItr(GetWorld()); ActorItr; ++ActorItr)
	{
		if (SpawnPos1.X == 0.0f)
		{
			SpawnPos1 = ActorItr->GetActorLocation();
		}
		else if (SpawnPos2.X == 0.0f)
		{
			SpawnPos2 = ActorItr->GetActorLocation();
		}
	}

	FActorSpawnParameters SpawnParams;

	AFTLPrototypeAI* pAI1 = GetWorld()->SpawnActor<AFTLPrototypeAI>(AIClass, SpawnPos1, FRotator(0, 0, 0), SpawnParams);
	AFTLPrototypeAI* pAI2 = GetWorld()->SpawnActor<AFTLPrototypeAI>(AIClass, SpawnPos2, FRotator(0, 0, 0), SpawnParams);

}

