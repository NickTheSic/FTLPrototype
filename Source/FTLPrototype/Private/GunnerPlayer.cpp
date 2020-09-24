// Fill out your copyright notice in the Description page of Project Settings.


#include "GunnerPlayer.h"

AGunnerPlayer::AGunnerPlayer()
{
	//this->Tags.Add("Gunner");
	classInformation.playerClass = PlayerClass::Gunner;
}

void AGunnerPlayer::BeginPlay()
{
	Super::BeginPlay();

}
