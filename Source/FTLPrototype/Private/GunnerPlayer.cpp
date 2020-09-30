// Fill out your copyright notice in the Description page of Project Settings.


#include "GunnerPlayer.h"
#include "Engine/Engine.h"
#include "Components/SkeletalMeshComponent.h"
#include "DrawDebugHelpers.h"

AGunnerPlayer::AGunnerPlayer()
{
	this->Tags.Add("Gunner");
	classInformation.playerClass = PlayerClass::Gunner;

	//OPTIONAL: Once we know how to balance the players exactly we can set it here in code

}

void AGunnerPlayer::SetupPlayerInputComponent(UInputComponent * PlayerInputComponent)
{
	SetupPlayerInputComponent(PlayerInputComponent);


}

void AGunnerPlayer::BeginPlay()
{
	Super::BeginPlay();

	if (pWeaponMesh)
	{
		pWeaponMesh->SetDebugDrawColor(FColor::Green);
	}

}

void AGunnerPlayer::ClassSpecialty()
{
	GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Red, "Gunner Class Special");



}
