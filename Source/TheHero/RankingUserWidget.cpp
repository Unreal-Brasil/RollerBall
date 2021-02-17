// Fill out your copyright notice in the Description page of Project Settings.

#include "RankingUserWidget.h"
#include "Blueprint/UserWidget.h"
#include "Components/HorizontalBox.h"
#include "Components/TextBlock.h"
#include "Components/VerticalBox.h"
#include "Engine/Blueprint.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include "RankingItemUserWidget.h"
#include "TP_Rolling/TP_RollingGameMode.h"
#include "TheHeroInstance.h"
#include "UObject/ConstructorHelpers.h"
#include "UObject/SoftObjectPath.h"


URankingUserWidget::URankingUserWidget(
    const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer) {

    ConstructorHelpers::FClassFinder<UUserWidget> ItemRankingClassFinder(TEXT("/Game/UI/WBP_ItemRanking"));
    
    if(ItemRankingClassFinder.Class){
        ItemRankingClass = ItemRankingClassFinder.Class;
    }
    
}

void URankingUserWidget::UpdateRanking() {
    if (TheHeroInstance != nullptr) {
        TheHeroInstance->RecuperarRankingGlobal();
    }
}
void URankingUserWidget::OnRecuperarRankingGlobal(const TArray<struct FRankingItemUserData>& RankingGlobal) {

    RemoveAllItems();

    auto PC = GetWorld()->GetFirstPlayerController();
    if (ItemRankingClass) {
        if (RankingGlobal.Num()) {
            for (auto&& i : RankingGlobal) {
                if (PC) {
                    URankingItemUserWidget* MyItem = CreateWidget<URankingItemUserWidget>(this, ItemRankingClass);
                    MyItem->PosicaoRanking->SetText(FText::FromString(i.PosicaoRanking));
                    MyItem->LoginUsuario->SetText(FText::FromString(i.LoginUsuario));
                    MyItem->PontuacaoUsuario->SetText(FText::FromString(i.PontuacaoUsuario));
                    RankingList->AddChildToVerticalBox(MyItem);
                }
            }
        }
    }
}

void URankingUserWidget::NativeConstruct() {
    Super::NativeConstruct();

    auto GI = UGameplayStatics::GetGameInstance(GetWorld());
    if (GI) {
        TheHeroInstance = Cast<UTheHeroInstance>(GI);
    }

    TheHeroInstance->OnRecuperarRankingGlobalResultSuccess.AddDynamic(this, &URankingUserWidget::OnRecuperarRankingGlobal);

    GetWorld()->GetTimerManager().SetTimer(DelayToRefreshRanking, this, &URankingUserWidget::UpdateRanking, 3.0f, true, 2.0f);
}

void URankingUserWidget::RemoveAllItems() {
    if (RankingList) {
        RankingList->ClearChildren();
    }
}
