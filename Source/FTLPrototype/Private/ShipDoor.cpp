// Fill out your copyright notice in the Description page of Project Settings.


#include "ShipDoor.h"
#include "MyPointLightComponent.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
AShipDoor::AShipDoor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	pLight = CreateDefaultSubobject<UMyPointLightComponent>("Point Light");
	pLight->LightColor = FColor::Blue;
	pLight->Intensity = Intensity;

	pMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));


}

// Called when the game starts or when spawned
void AShipDoor::BeginPlay()
{
	Super::BeginPlay();
	
}

void AShipDoor::Activate()
{
	if (pLight != nullptr)
	{
		pLight->SetLightColor(FColor::Purple);
	}

	bIsActivated ? Close() : Open();

}

void AShipDoor::Open()
{
	bIsActivated = true;
	if (pLight != nullptr)
	{
		pLight->StartEmergency();
	}
}


void AShipDoor::Close()
{
	bIsActivated = false;
	if (pLight != nullptr)
	{
		pLight->EndEmergency();
	}
}

