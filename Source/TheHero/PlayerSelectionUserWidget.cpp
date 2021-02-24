// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerSelectionUserWidget.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Styling/SlateColor.h"
#include "TheHeroInstance.h"





void UPlayerSelectionUserWidget::NativeConstruct()
{
    auto GI = UGameplayStatics::GetGameInstance(GetWorld());
    if (GI)
    {
        TheHeroInstance = Cast<UTheHeroInstance>(GI);
    }


    if (btnSelParede) {
        btnSelParede->OnClicked.AddDynamic(this, &UPlayerSelectionUserWidget::OnBtnSelParede);
    }
    if (btnSelFosca) {
        btnSelFosca->OnClicked.AddDynamic(this, &UPlayerSelectionUserWidget::OnBtnSelFosca);
    }
    if (btnSelParalele) {
        btnSelParalele->OnClicked.AddDynamic(this, &UPlayerSelectionUserWidget::OnBtnSelParalele);
    }
    if (btnSelPolida) {
        btnSelPolida->OnClicked.AddDynamic(this, &UPlayerSelectionUserWidget::OnBtnSelPolida);
    }
    if (btnSelPrata) {
        btnSelPrata->OnClicked.AddDynamic(this, &UPlayerSelectionUserWidget::OnBtnSelPrata);
    }
    if (btnSelScifi) {
        btnSelScifi->OnClicked.AddDynamic(this, &UPlayerSelectionUserWidget::OnBtnSelScifi);
    }
    if (btnSelOuro) {
        btnSelOuro->OnClicked.AddDynamic(this, &UPlayerSelectionUserWidget::OnBtnSelOuro);
    }
}

void UPlayerSelectionUserWidget::ClearTextColors()
{
    FSlateColor newColor = FSlateColor(FLinearColor(1.0f, 1.0f, 1.0f, 1.0f));

    TxtParede->SetColorAndOpacity(newColor);
    TxtFosca->SetColorAndOpacity(newColor);
    TxtParalele->SetColorAndOpacity(newColor);
    TxtPolida->SetColorAndOpacity(newColor);
    TxtPrata->SetColorAndOpacity(newColor);
    TxtScifi->SetColorAndOpacity(newColor);
    TxtOuro->SetColorAndOpacity(newColor);
}

void UPlayerSelectionUserWidget::OnBtnSelParede()
{
    if (TheHeroInstance != nullptr) {
        ClearTextColors();
        TxtParede->SetColorAndOpacity(TextColorSelected);
        TheHeroInstance->SetPlayer(EPlayerTypeSelection::PedraParede);
    }
}

void UPlayerSelectionUserWidget::OnBtnSelFosca()
{
    if (TheHeroInstance != nullptr) {
        ClearTextColors();
        TxtFosca->SetColorAndOpacity(TextColorSelected);
        TheHeroInstance->SetPlayer(EPlayerTypeSelection::MadeiraFosca);
    }
}

void UPlayerSelectionUserWidget::OnBtnSelParalele()
{
    if (TheHeroInstance != nullptr) {
        ClearTextColors();
        TxtParalele->SetColorAndOpacity(TextColorSelected);
        TheHeroInstance->SetPlayer(EPlayerTypeSelection::PedraParalelepipedo);
    }
}

void UPlayerSelectionUserWidget::OnBtnSelPolida()
{
    if (TheHeroInstance != nullptr) {
        ClearTextColors();
        TxtPolida->SetColorAndOpacity(TextColorSelected);
        TheHeroInstance->SetPlayer(EPlayerTypeSelection::MadeiraPolida);
    }
}

void UPlayerSelectionUserWidget::OnBtnSelPrata()
{
    if (TheHeroInstance != nullptr) {
        ClearTextColors();
        TxtPrata->SetColorAndOpacity(TextColorSelected);
        TheHeroInstance->SetPlayer(EPlayerTypeSelection::MetalPrata);
    }
}

void UPlayerSelectionUserWidget::OnBtnSelScifi()
{
    if (TheHeroInstance != nullptr) {
        ClearTextColors();
        TxtScifi->SetColorAndOpacity(TextColorSelected);
        TheHeroInstance->SetPlayer(EPlayerTypeSelection::MetalScifi);
    }
}

void UPlayerSelectionUserWidget::OnBtnSelOuro()
{
    if (TheHeroInstance != nullptr) {
        ClearTextColors();
        TxtOuro->SetColorAndOpacity(TextColorSelected);
        TheHeroInstance->SetPlayer(EPlayerTypeSelection::MetalOuro);
    }
}
