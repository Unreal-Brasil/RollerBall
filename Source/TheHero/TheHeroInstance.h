// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "TheHeroInstance.generated.h"

/**
 *
 */
UCLASS()
class THEHERO_API UTheHeroInstance : public UGameInstance
{
	GENERATED_BODY()

public:

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "PlayerScore")
		int PlayerScore;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "PlayerScore")
		int PlayerTime;

	UFUNCTION(BlueprintCallable)
		void ResetPlayerValues(int valor);



	UFUNCTION(BlueprintCallable)
		void UpdatePlayerScore(int valor);

	UFUNCTION(BlueprintCallable)
		FORCEINLINE	int RetrievePlayerScore() const { return PlayerScore; };


	UFUNCTION(BlueprintCallable)
		void UpdatePlayerTime(int valor);

	UFUNCTION(BlueprintCallable)
		FORCEINLINE	int RetrievePlayerTime() const { return PlayerTime; };

};
