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

protected:
	virtual void BeginPlay() override;

};
