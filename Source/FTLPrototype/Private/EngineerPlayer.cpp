// Fill out your copyright notice in the Description page of Project Settings.


#include "EngineerPlayer.h"

AEngineerPlayer::AEngineerPlayer()
{
	this->Tags.Add("Engineer");
	classInformation.playerClass = PlayerClass::Engineer;

	//OPTIONAL: Once we know how to balance the players exactly we can set it here in code

}

void AEngineerPlayer::BeginPlay()
{
	Super::BeginPlay();
}