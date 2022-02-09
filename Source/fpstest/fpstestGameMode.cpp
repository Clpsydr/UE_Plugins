// Copyright Epic Games, Inc. All Rights Reserved.

#include "fpstestGameMode.h"
#include "fpstestHUD.h"
#include "fpstestCharacter.h"
#include "UObject/ConstructorHelpers.h"

AfpstestGameMode::AfpstestGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPersonCPP/Blueprints/FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = AfpstestHUD::StaticClass();
}
