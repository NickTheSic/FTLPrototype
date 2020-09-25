// Fill out your copyright notice in the Description page of Project Settings.


#include "GunnerPlayer.h"

AGunnerPlayer::AGunnerPlayer()
{
	this->Tags.Add("Gunner");
	classInformation.playerClass = PlayerClass::Gunner;

	//OPTIONAL: Once we know how to balance the players exactly we can set it here in code

}

void AGunnerPlayer::BeginPlay()
{
	Super::BeginPlay();

}
