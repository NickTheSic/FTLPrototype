// Fill out your copyright notice in the Description page of Project Settings.


#include "EngineerPlayer.h"

AEngineerPlayer::AEngineerPlayer()
{
	//this->Tags.Add("Engineer");
	classInformation.playerClass = PlayerClass::Engineer;
}

void AEngineerPlayer::BeginPlay()
{
	Super::BeginPlay();
}