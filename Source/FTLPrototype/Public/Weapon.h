// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Item.h"
#include "Weapon.generated.h"

/**
 * 
 */
UCLASS()
class FTLPROTOTYPE_API AWeapon : public AItem
{
	GENERATED_BODY()

public:
	//sets defaults, calls parent constructor?
	AWeapon();

protected:
	bool bIsFiring;				//if the weapon is firing/attacking
	
	uint64 uiMagAmmo;			//ammo currently in the magazine
	uint64 uiMaxMagAmmo;		//maximum amount of ammo you can have in your magazine
	
	int iReserveAmmo;			//ammo pool to draw from (-1 for infinite ammo supply)
	uint64 uiMaxReserveAmmo;	//maximum amount of ammo you can have in your ammo pool

	float fReloadTime;			//Time it takes to reload (attack cooldown for melee)

public:
	//For when an item is used/done being used I.e. pressing a button
	virtual void Use() override;
	virtual void StopUse() override;

	//In case we need to obliterate an item from existance
	virtual void Destroy() override;

	//To turn on/off items, to hide/show items, and whatever else you'd want switched on/off
	virtual void Enable() override;
	virtual void Disable() override;

	//For handling behaviour before, during, and after shooting
	virtual void FireStart();
	virtual void Fire();
	virtual void FireEnd();

	//For reloading the weapon
	virtual void Reload();
};
