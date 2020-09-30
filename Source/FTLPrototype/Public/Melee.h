// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Weapon.h"
#include "../Public/RaycastComponent.h"
#include "Melee.generated.h"

/**
 * 
 */
UCLASS()
class FTLPROTOTYPE_API AMelee : public AWeapon
{
	GENERATED_BODY()
public:
	AMelee();
	virtual void Tick(float deltaTime) override;

protected:
	virtual void BeginPlay() override;

public:
	URaycastComponent* pRayCast;

	//For handling behaviour before, during, and after shooting
	virtual void FireStart() override;
	virtual void Fire() override;
	virtual void FireEnd() override;
};
