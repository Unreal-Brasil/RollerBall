// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HUDUserWidget.generated.h"

/**
 *
 */
UCLASS()
class THEHERO_API UHUDUserWidget : public UUserWidget
{
	GENERATED_BODY()

private:
	class ATP_RollingGameMode* RollingGameMode;
	class UTheHeroInstance* TheHeroInstance;

	UFUNCTION()
		void OnCountDownUpdate(int Counter);

public:
	UHUDUserWidget(const FObjectInitializer& ObjectInitializer);
	// Optionally override the Blueprint "Event Construct" event
	virtual void NativeConstruct() override;

	// Optionally override the tick event
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;


	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		class UTextBlock* ScoreIncrement = nullptr;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		class UTextBlock* UserLogin = nullptr;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		class UTextBlock* PlayerTime = nullptr;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		class UTextBlock* CountDownToRestart = nullptr;

};
