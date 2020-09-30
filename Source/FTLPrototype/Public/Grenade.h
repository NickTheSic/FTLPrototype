// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Weapon.h"
#include "Grenade.generated.h"

/**
 * 
 */
UCLASS()
class FTLPROTOTYPE_API AGrenade : public AWeapon
{
	GENERATED_BODY()
	
public:
	AGrenade();
	virtual void Tick(float deltaTime) override;

protected:
	virtual void BeginPlay() override;

public:
	//For handling behaviour before, during, and after shooting
	virtual void FireStart() override;
	virtual void Fire() override;
	virtual void FireEnd() override;

};
