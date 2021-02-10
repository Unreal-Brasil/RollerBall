// Copyright Epic Games, Inc. All Rights Reserved.

#include "TP_RollingGameMode.h"
#include "TP_RollingBall.h"
#include "TheHero/TheHeroInstance.h"

ATP_RollingGameMode::ATP_RollingGameMode()
{
	PrimaryActorTick.bCanEverTick = true;

	IsClosed = false;

	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/RollingCPP/Blueprint/TP_RollingBallPlayer"));
	if (PlayerPawnBPClass.Class != nullptr)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}

void ATP_RollingGameMode::BeginPlay()
{
	Super::BeginPlay();
	auto GI = GetGameInstance();
	if (GI != nullptr) {
		CurrentGameInstance = Cast<UTheHeroInstance>(GI);
	}
}

void ATP_RollingGameMode::Tick(float DeltaTime)
{
	if (IsClosed)return;

	if (CurrentGameInstance != nullptr)
	{
		const int ptimer = CurrentGameInstance->RetrievePlayerTime();
		const int pscore = CurrentGameInstance->RetrievePlayerScore();

		if (ptimer > 10) {
			if (pscore < ptimer) {
				OnPlayerDied.Broadcast();
				IsClosed = true;
			}
		}
	}
}
