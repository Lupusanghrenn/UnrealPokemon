// Copyright Epic Games, Inc. All Rights Reserved.

#include "UnrealPokemonGameMode.h"
#include "UnrealPokemonCharacter.h"
#include "UObject/ConstructorHelpers.h"

AUnrealPokemonGameMode::AUnrealPokemonGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
