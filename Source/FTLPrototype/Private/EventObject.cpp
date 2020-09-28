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

	pActiveMaterial = CreateDefaultSubobject<UMaterial>("ActiveMaterial");
	pDeactiveMaterial = CreateDefaultSubobject<UMaterial>("DeactiveMaterial");

	pInteractableBox = CreateDefaultSubobject<UInteractableBox>("Collider");
	pInteractableBox->SetupAttachment(RootComponent);

	Tags.Add("SystemEvent");

	bisActive = false;
}

// Called when the game starts or when spawned
void AEventObject::BeginPlay()
{
	Super::BeginPlay();

	Deactivate();

}

// Called every frame
void AEventObject::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	
}

void AEventObject::Activate()
{
	bisActive = true;
	pStaticMesh->SetMaterial(0, pActiveMaterial);
}

void AEventObject::Deactivate()
{
	bisActive = false;
	pStaticMesh->SetMaterial(0, pDeactiveMaterial);
	float fRandomActivation = FMath::RandRange(3.0f, 6.0f);
	GetWorld()->GetTimerManager().SetTimer(ActivationTimer, this, &AEventObject::Activate, fRandomActivation, false);
}

bool AEventObject::IsActive()
{
	return bisActive;
}

