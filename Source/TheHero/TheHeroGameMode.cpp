// Copyright Epic Games, Inc. All Rights Reserved.

#include "TheHeroGameMode.h"
#include "TheHeroCharacter.h"
#include "UObject/ConstructorHelpers.h"

ATheHeroGameMode::ATheHeroGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/SideScrollerCPP/Blueprints/SideScrollerCharacter"));
	if (PlayerPawnBPClass.Class != nullptr)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
