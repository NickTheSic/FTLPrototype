// Fill out your copyright notice in the Description page of Project Settings.


#include "MedicPlayer.h"

AMedicPlayer::AMedicPlayer()
{
	this->Tags.Add("Medic");
	classInformation.playerClass = PlayerClass::Medic;

	//OPTIONAL: Once we know how to balance the players exactly we can set it here in code

}

void AMedicPlayer::BeginPlay()
{
}
