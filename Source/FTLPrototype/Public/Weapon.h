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
	//sets defaults
	AWeapon();
	virtual void Tick(float deltaTime) override;

protected:

	virtual void BeginPlay() override;

	//Can be edited anywhere, reads/writes from blueprint, under weapon stats, allows private variables to be accessed
	UPROPERTY(EditAnywhere, Category = "Weapon Stats", meta = (AllowPrivateAccess = "true"))
		bool bIsFiring;				//if the weapon is firing/attacking
	UPROPERTY(EditAnywhere, Category = "Weapon Stats", meta = (AllowPrivateAccess = "true"))
		bool bIsAutomatic;			//if the weapon's trigger can be held or has to be pulled every shot I.e. Machine Gun vs Pistol

	UPROPERTY(EditAnywhere, Category = "Weapon Stats", meta = (AllowPrivateAccess = "true"))
		uint64 uiMagAmmo;			//ammo currently in the magazine
	UPROPERTY(EditAnywhere, Category = "Weapon Stats", meta = (AllowPrivateAccess = "true"))
		uint64 uiMaxMagAmmo;		//maximum amount of ammo you can have in your magazine

	UPROPERTY(EditAnywhere, Category = "Weapon Stats", meta = (AllowPrivateAccess = "true"))
		int iReserveAmmo;			//ammo pool to draw from (-1 for infinite ammo supply)
	UPROPERTY(EditAnywhere, Category = "Weapon Stats", meta = (AllowPrivateAccess = "true"))
		uint64 uiMaxReserveAmmo;	//maximum amount of ammo you can have in your ammo pool

	UPROPERTY(EditAnywhere, Category = "Weapon Stats", meta = (AllowPrivateAccess = "true"))
		float fReloadTime;			//Time it takes to reload
	UPROPERTY(EditAnywhere, Category = "Weapon Stats", meta = (AllowPrivateAccess = "true"))
		float fFireRate;			//How many shots per second (1.0f / firerate on shoot timer)

public:

	FTimerHandle attackTimer;
	FTimerHandle reloadTimer;

	//For handling behaviour before, during, and after shooting
	virtual void FireStart();
	virtual void Fire();
	virtual void FireEnd();

	//For reloading the weapon
	virtual void ReloadStart();
	virtual void Reload();
	virtual void ReloadEnd();

	//Type of weapon you're using (just in case we need it somewhere)
	enum WeaponType
	{
		Weapon,		//Default
		Gun,		//Gun
		Melee,		//Melee
		Grenade		//Grenade
	};
};
