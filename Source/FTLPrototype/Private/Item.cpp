// Fill out your copyright notice in the Description page of Project Settings.

#include "Item.h"
#include "Engine/Engine.h"

// Sets default values
AItem::AItem()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	pSkeletalMesh = CreateDefaultSubobject<USkeletalMeshComponent>("Mesh");
	RootComponent = pSkeletalMesh;	//Mesh is root component

	pHitBox = CreateDefaultSubobject<UBoxComponent>("Hit Box");
	pHitBox->SetCollisionProfileName("BlockAll");
	pHitBox->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AItem::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AItem::Use()
{
	//Functionality for using an item
}

void AItem::StopUse()
{
	//Functionality for after using an item
}

void AItem::Destroy()
{
	//Doubt we'll use this but if we need to destroy it
}

void AItem::Enable()
{
	//This shows and activates all necessary things
	pSkeletalMesh->SetSimulatePhysics(true);
	pSkeletalMesh->SetCollisionProfileName("BlockAll");
	SetActorHiddenInGame(false);
	SetActorEnableCollision(true);
	SetActorTickEnabled(true);
}

void AItem::Disable()
{
	//This hides and deactivates all necessary things
	pSkeletalMesh->SetSimulatePhysics(false);
	pSkeletalMesh->SetCollisionProfileName("NoCollision");
	SetActorHiddenInGame(true);
	SetActorEnableCollision(false);
	SetActorTickEnabled(false);
}