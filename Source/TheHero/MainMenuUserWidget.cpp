// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenuUserWidget.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "Components/SlateWrapperTypes.h"
#include "Components/WidgetSwitcher.h"
#include "Kismet/GameplayStatics.h"
#include "TP_Rolling/TP_RollingGameMode.h"
#include "Components/EditableTextBox.h"
#include "Kismet/KismetSystemLibrary.h"
#include "TheHeroInstance.h"




UMainMenuUserWidget::UMainMenuUserWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{

}

void UMainMenuUserWidget::NativeConstruct()
{
    Super::NativeConstruct();

    auto GM = UGameplayStatics::GetGameMode(GetWorld());
    if (GM) {
        RollingGameMode = Cast<ATP_RollingGameMode>(GM);
    }

    auto GI = UGameplayStatics::GetGameInstance(GetWorld());
    if (GI)
    {
        TheHeroInstance = Cast<UTheHeroInstance>(GI);
    }

    if (BtnSelLogin) {
        BtnSelLogin->OnClicked.AddDynamic(this, &UMainMenuUserWidget::OnBtnSelLoginClicked);
    }
    if (BtnSelCadastro) {
        BtnSelCadastro->OnClicked.AddDynamic(this, &UMainMenuUserWidget::OnBtnSelCadastroClicked);
    }
    if (BtnSelSetup) {
        BtnSelSetup->OnClicked.AddDynamic(this, &UMainMenuUserWidget::OnBtnSelSetupClicked);
    }
    if (BtnIniciarPartida) {
        BtnIniciarPartida->OnClicked.AddDynamic(this, &UMainMenuUserWidget::OnIniciarPartidaClicked);
    }
    if (BtnSair) {
        BtnSair->OnClicked.AddDynamic(this, &UMainMenuUserWidget::OnBtnSairClicked);
    }
    if (BtnCadastrar) {
        BtnCadastrar->OnClicked.AddDynamic(this, &UMainMenuUserWidget::OnBtnCadastrarClicked);
    }
}

void UMainMenuUserWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
    Super::NativeTick(MyGeometry, InDeltaTime);
}

void UMainMenuUserWidget::OnBtnSelLoginClicked()
{
    if (SelectWidgetSwitcher) {
        SelectWidgetSwitcher->SetActiveWidgetIndex(0);
    }
}

void UMainMenuUserWidget::OnBtnSelCadastroClicked()
{
    if (SelectWidgetSwitcher) {
        SelectWidgetSwitcher->SetActiveWidgetIndex(1);
    }

}

void UMainMenuUserWidget::OnBtnSelSetupClicked()
{
    if (SelectWidgetSwitcher) {
        SelectWidgetSwitcher->SetActiveWidgetIndex(2);
    }

}

void UMainMenuUserWidget::OnIniciarPartidaClicked()
{
    if (TheHeroInstance) {
        TheHeroInstance->OnLoginResultSuccess.AddDynamic(this, &UMainMenuUserWidget::OnLoginSuccess);
        TheHeroInstance->OnLoginResultError.AddDynamic(this, &UMainMenuUserWidget::OnLoginError);
        FString UserName = LoginUsuario->GetText().ToString();
        FString Password = LoginSenha->GetText().ToString();

        TheHeroInstance->DoLogin(UserName, Password);
    }
}

void UMainMenuUserWidget::OnBtnSairClicked()
{
    auto PC = UGameplayStatics::GetPlayerController(GetWorld(), 0);
    if (PC)
    {
        UKismetSystemLibrary::QuitGame(GetWorld(), PC, EQuitPreference::Type::Quit, false);
    }
}

void UMainMenuUserWidget::OnBtnCadastrarClicked()
{
    if (TheHeroInstance) {
        TheHeroInstance->OnCadastroReultSuccess.AddDynamic(this, &UMainMenuUserWidget::OnCadastroSuccess);
        TheHeroInstance->OnCadastroReultError.AddDynamic(this, &UMainMenuUserWidget::OnCadastroError);
        FString UserName = CadastroUsuario->GetText().ToString();
        FString Password = CadastroSenha->GetText().ToString();
        FString Email = CadastroEmail->GetText().ToString();

        TheHeroInstance->DoCadastro(UserName, Password, Email);
    }

}

void UMainMenuUserWidget::OnCadastroSuccess(int Id, FString Login, FString SuccessMessage)
{
    MensagemErroCadastro->SetText(FText::FromString(SuccessMessage));
    GetWorld()->GetTimerManager().SetTimer(DelayToChangeSelection, this, &UMainMenuUserWidget::ChangePageSelection, 3, false);
}
void UMainMenuUserWidget::OnCadastroError(FString ErrorMessage)
{
    MensagemErroCadastro->SetText(FText::FromString(ErrorMessage));
}

void UMainMenuUserWidget::ChangePageSelection()
{
    GetWorld()->GetTimerManager().ClearTimer(DelayToChangeSelection);

    if (SelectWidgetSwitcher) {
        SelectWidgetSwitcher->SetActiveWidgetIndex(0);
    }
}

void UMainMenuUserWidget::OnLoginSuccess(int Id, FString Login, FString Token, FString SuccessMessage)
{
    UGameplayStatics::OpenLevel(GetWorld(), "L1");
}

void UMainMenuUserWidget::OnLoginError(FString ErrorMessage)
{
    MensagemErroLogin->SetText(FText::FromString(ErrorMessage));
}
