// Fill out your copyright notice in the Description page of Project Settings.


#include "EventObject.h"
#include "InteractableBox.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "Materials/Material.h"

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
}

// Called when the game starts or when spawned
void AEventObject::BeginPlay()
{
	Super::BeginPlay();

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

	//Temporary for prototype, will randomly activate from a set value
	float fRandomActivation = FMath::RandRange(5.0f, 20.0f);
	GetWorld()->GetTimerManager().SetTimer(ActivationTimer, this, &AEventObject::Activate, fRandomActivation, false);
}

void AEventObject::LowerHealth()
{

}

void AEventObject::LowerOxygen()
{

}

void AEventObject::SpawnEnemy()
{

}

