// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "TP_RollingGameMode.generated.h"

UCLASS(minimalapi)
class ATP_RollingGameMode : public AGameModeBase
{
	GENERATED_BODY()

	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FPlayerDied);

public:
	ATP_RollingGameMode();

	UPROPERTY(BlueprintAssignable)
	FPlayerDied OnPlayerDied;

private:
	class UTheHeroInstance *CurrentGameInstance;
	bool IsClosed;

	UFUNCTION()
	void OnPlayerDiedNow();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
};
