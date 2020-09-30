// Fill out your copyright notice in the Description page of Project Settings.


#include "Grenade.h"

AGrenade::AGrenade()
{
    bIsFiring = false;
    bIsAutomatic = false;
    uiMagAmmo = 1;
    uiMaxMagAmmo = 1;
    iReserveAmmo = 0;
    uiMaxReserveAmmo = 0;
    fReloadTime = 0.0f;
    fFireRate = 5.0f;   //time to explode

    PrimaryActorTick.bCanEverTick = false;
}

void AGrenade::Tick(float deltaTime)
{
    Super::Tick(deltaTime);

    //rTodo: while aiming, draw trajectory
    if (bIsFiring == true)
    {

    }
}

void AGrenade::BeginPlay()
{
    Super::BeginPlay();
}

void AGrenade::FireStart()
{
    if (uiMagAmmo != 0)
    {
        uiMagAmmo--;
        //start timer, call once
        FTimerManager& Timer = GetWorldTimerManager();
        Timer.SetTimer(attackTimer, this, &AGrenade::Fire, 0.1f, false, fFireRate);
        bIsFiring = true;
    }
}

void AGrenade::Fire()
{
    //rTodo: do explosion

    //delete grenade
    Disable();
}

void AGrenade::FireEnd()
{
    //stops showing trajectory
    bIsFiring = false;

    //rTodo: Throw grenade along trajectory
    //...
}