// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePlayer.h"
#include "GunnerPlayer.generated.h"

/**
 * 
 */
UCLASS()
class FTLPROTOTYPE_API AGunnerPlayer : public ABasePlayer
{
	GENERATED_BODY()

public:
	AGunnerPlayer();

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	virtual void BeginPlay() override;

	virtual void ClassSpecialty() override;
	
};
