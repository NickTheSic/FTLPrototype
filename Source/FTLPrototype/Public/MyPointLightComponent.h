// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/PointLightComponent.h"
#include "MyPointLightComponent.generated.h"

/**
 * 
 */
UCLASS(meta = (BlueprintSpawnableComponent))
class FTLPROTOTYPE_API UMyPointLightComponent : public UPointLightComponent
{
	GENERATED_BODY()
	
public:

	void StartEmergency() { SetLightColor(FColor::Red); }
	void EndEmergency() { SetLightColor(FColor::Green); }

};
