// Copyright 1998-2014 Epic Games, Inc. All Rights Reserved.

#include "hleoni_CTP.h"
#include "hleoni_CTPGameMode.h"
#include "hleoni_CTPHUD.h"

Ahleoni_CTPGameMode::Ahleoni_CTPGameMode(const class FPostConstructInitializeProperties& PCIP)
	: Super(PCIP)
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/Blueprints/MyCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = Ahleoni_CTPHUD::StaticClass();
}
