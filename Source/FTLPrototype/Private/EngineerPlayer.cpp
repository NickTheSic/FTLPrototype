// Fill out your copyright notice in the Description page of Project Settings.


#include "EngineerPlayer.h"

AEngineerPlayer::AEngineerPlayer()
{
	this->Tags.Add("Engineer");
	classInformation.playerClass = PlayerClass::Engineer;

	//OPTIONAL: Once we know how to balance the players exactly we can set it here in code

}

void AEngineerPlayer::SetupPlayerInputComponent(UInputComponent * PlayerInputComponent)
{
	SetupPlayerInputComponent(PlayerInputComponent);

}

void AEngineerPlayer::BeginPlay()
{
	Super::BeginPlay();
}

void AEngineerPlayer::ClassSpecialty()
{
	GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Red, "Engineer Class Special");

}
