// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Weapon.h"
#include "../Public/RaycastComponent.h"
#include "GunRifle.generated.h"

/**
 * 
 */
UCLASS()
class FTLPROTOTYPE_API AGunRifle : public AWeapon
{
	GENERATED_BODY()
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon")
	TSubclassOf<class UDamageType> DamageType;

public:
	AGunRifle();

	virtual void Tick(float deltaTime) override;

	URaycastComponent* pRayCast;



	//For handling behaviour before, during, and after shooting
	virtual void FireStart() override;
	virtual void Fire() override;
	virtual void FireEnd() override;

	//For reloading the weapon
	virtual void ReloadStart() override;
	virtual void Reload() override;
	virtual void ReloadEnd() override;

protected:
	virtual void BeginPlay() override;
};
