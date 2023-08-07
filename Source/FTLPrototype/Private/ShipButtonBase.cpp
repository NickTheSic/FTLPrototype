// Fill out your copyright notice in the Description page of Project Settings.


#include "ShipButtonBase.h"
#include "ShipDoor.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
AShipButtonBase::AShipButtonBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Tags.Add("Button");

	pMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));

}

// Called when the game starts or when spawned
void AShipButtonBase::BeginPlay()
{
	Super::BeginPlay();
	
}

void AShipButtonBase::Activate()
{
	if (pObjectToActivate != nullptr)
	{
		pObjectToActivate->Activate();
	}
}

