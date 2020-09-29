// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon.h"

AWeapon::AWeapon()
{
    bIsFiring = false;
    bIsAutomatic = false;
    uiMagAmmo = 0;
    uiMaxMagAmmo = 0;
    iReserveAmmo = 0;
    uiMaxReserveAmmo = 0;
    fReloadTime = 0.0f;
}

void AWeapon::FireStart()
{
    //Beginning code for firing
    //This is where we start animations and shooting timers
}

void AWeapon::Fire()
{
    //Code for firing and damage handling
    //ONLY SHOOT IF WE HAVE AMMO
    //IF NO AMMO, STOP FIRING AND RELOAD
}

void AWeapon::FireEnd()
{
    //Clearing timers and any 
}

void AWeapon::ReloadStart()
{
    //Beginning of reload
}

void AWeapon::Reload()
{
    //Actually reload based on reload time
}

void AWeapon::ReloadEnd()
{
    //End of reload
}