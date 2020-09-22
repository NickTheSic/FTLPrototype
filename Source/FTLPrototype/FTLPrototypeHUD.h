// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once 

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "FTLPrototypeHUD.generated.h"

UCLASS()
class AFTLPrototypeHUD : public AHUD
{
	GENERATED_BODY()

public:
	AFTLPrototypeHUD();

	/** Primary draw call for the HUD */
	virtual void DrawHUD() override;

private:
	/** Crosshair asset pointer */
	class UTexture2D* CrosshairTex;

};

