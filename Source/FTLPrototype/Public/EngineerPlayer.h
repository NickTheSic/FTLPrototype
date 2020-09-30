// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePlayer.h"
#include "EngineerPlayer.generated.h"

/**
 * 
 */
UCLASS()
class FTLPROTOTYPE_API AEngineerPlayer : public ABasePlayer
{
	GENERATED_BODY()
	
public:
	AEngineerPlayer();

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:

	virtual void BeginPlay() override;

	virtual void ClassSpecialty() override;

};
