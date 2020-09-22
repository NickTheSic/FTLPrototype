// Copyright Epic Games, Inc. All Rights Reserved.

#include "FTLPrototypeGameMode.h"
#include "FTLPrototypeHUD.h"
#include "FTLPrototypeCharacter.h"
#include "UObject/ConstructorHelpers.h"

AFTLPrototypeGameMode::AFTLPrototypeGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPersonCPP/Blueprints/FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = AFTLPrototypeHUD::StaticClass();
}
