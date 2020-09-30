// Fill out your copyright notice in the Description page of Project Settings.


#include "EngineerPlayer.h"
#include "Components/SkeletalMeshComponent.h"
#include "DrawDebugHelpers.h"

AEngineerPlayer::AEngineerPlayer()
{
	this->Tags.Add("Engineer");
	classInformation.playerClass = PlayerClass::Engineer;

	//OPTIONAL: Once we know how to balance the players exactly we can set it here in code

}

void AEngineerPlayer::SetupPlayerInputComponent(UInputComponent * PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AEngineerPlayer::BeginPlay()
{
	Super::BeginPlay();

	if (pWeaponMesh)
	{
		pWeaponMesh->SetDebugDrawColor(FColor::Orange);
	}
}

void AEngineerPlayer::ClassSpecialty()
{
	GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Red, "Engineer Class Special");

}
