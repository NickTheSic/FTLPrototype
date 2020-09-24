// Fill out your copyright notice in the Description page of Project Settings.


#include "MedicPlayer.h"

AMedicPlayer::AMedicPlayer()
{
	this->Tags.Add("Medic");
	classInformation.playerClass = PlayerClass::Medic;
}

void AMedicPlayer::BeginPlay()
{
}
