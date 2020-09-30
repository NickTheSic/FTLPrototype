// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePlayer.h"
#include "MedicPlayer.generated.h"

/**
 * 
 */
UCLASS()
class FTLPROTOTYPE_API AMedicPlayer : public ABasePlayer
{
	GENERATED_BODY()
public:
	AMedicPlayer();

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	virtual void BeginPlay() override;

	virtual void ClassSpecialty() override;

	bool bHealingSelf = true; //Default to healing ourself I guess

	void HealSelf();
	void HealOther(ABasePlayer* other);
	
};
