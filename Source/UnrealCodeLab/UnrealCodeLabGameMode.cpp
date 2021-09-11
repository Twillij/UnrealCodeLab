// Copyright Epic Games, Inc. All Rights Reserved.

#include "UnrealCodeLabGameMode.h"
#include "PlayerCharacter.h"
#include "UObject/ConstructorHelpers.h"

AUnrealCodeLabGameMode::AUnrealCodeLabGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/Characters/Player"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
