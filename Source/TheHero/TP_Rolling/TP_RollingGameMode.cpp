// Copyright Epic Games, Inc. All Rights Reserved.

#include "TP_RollingGameMode.h"
#include "TP_RollingBall.h"

ATP_RollingGameMode::ATP_RollingGameMode()
{
	// set default pawn class to our ball
	//DefaultPawnClass = ATP_RollingBall::StaticClass();

	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/RollingCPP/Blueprint/TP_RollingBallPlayer"));
	if (PlayerPawnBPClass.Class != nullptr)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
