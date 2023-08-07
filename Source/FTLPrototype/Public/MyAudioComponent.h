// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/AudioComponent.h"
#include "MyAudioComponent.generated.h"

/**
 * 
 */
UCLASS(meta = (BlueprintSpawnableComponent))
class FTLPROTOTYPE_API UMyAudioComponent : public UAudioComponent
{
	GENERATED_BODY()
	
public:

	UPROPERTY(EditAnywhere)
		USoundBase* soundOne;

	UPROPERTY(EditAnywhere)
		USoundBase* soundTwo;
	UFUNCTION(BlueprintCallable)
	void PlaySoundOne() { if (soundOne != nullptr) Sound = soundOne; Play(); }
	UFUNCTION(BlueprintCallable)
	void PlaySoundTwo() { if (soundTwo != nullptr) Sound = soundTwo; Play(); }

};
