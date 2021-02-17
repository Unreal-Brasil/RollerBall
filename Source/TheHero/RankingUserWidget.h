// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TheHeroInstance.h"
#include "RankingUserWidget.generated.h"

UCLASS()
class THEHERO_API URankingUserWidget : public UUserWidget
{
	GENERATED_BODY()

private:
	class UTheHeroInstance* TheHeroInstance;

	UFUNCTION()
		void OnRecuperarRankingGlobal(const TArray<FRankingItemUserData>& RankingGlobal);
	UFUNCTION()
		void UpdateRanking();

	FTimerHandle DelayToRefreshRanking;

	TSubclassOf<class UUserWidget> ItemRankingClass;
	
public:
	URankingUserWidget(const FObjectInitializer& ObjectInitializer);

	virtual void NativeConstruct() override;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		class UVerticalBox* RankingList = nullptr;

	void InsertItem(class URankingItemUserWidget* ItemRanking);
	void RemoveAllItems();

};
