// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PlayerSelectionUserWidget.generated.h"

/**
 *
 */
UCLASS()
class THEHERO_API UPlayerSelectionUserWidget : public UUserWidget
{
	GENERATED_BODY()
public:

	virtual void NativeConstruct() override;
	
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		class UButton* btnSelParede = nullptr;


	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		class UButton* btnSelFosca = nullptr;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		class UButton* btnSelParalele = nullptr;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		class UButton* btnSelPolida = nullptr;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		class UButton* btnSelPrata = nullptr;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		class UButton* btnSelScifi = nullptr;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		class UButton* btnSelOuro = nullptr;


	
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		class UTextBlock* TxtParede = nullptr;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		class UTextBlock* TxtFosca = nullptr;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		class UTextBlock* TxtParalele = nullptr;
	
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		class UTextBlock* TxtPolida = nullptr;
	

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		class UTextBlock* TxtPrata = nullptr;


	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		class UTextBlock* TxtScifi = nullptr;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		class UTextBlock* TxtOuro = nullptr;


private:
	class UTheHeroInstance* TheHeroInstance;
	
	struct FSlateColor TextColorSelected = FSlateColor(FLinearColor(1.0f, 0.0f, 0.0f, 1.0f));
	
	void ClearTextColors();


	UFUNCTION()
		void OnBtnSelParede();
	UFUNCTION()
		void OnBtnSelFosca();
	UFUNCTION()
		void OnBtnSelParalele();
	UFUNCTION()
		void OnBtnSelPolida();
	UFUNCTION()
		void OnBtnSelPrata();
	UFUNCTION()
		void OnBtnSelScifi();
	UFUNCTION()
		void OnBtnSelOuro();

	
};
