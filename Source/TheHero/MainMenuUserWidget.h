// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainMenuUserWidget.generated.h"

/**
 *
 */
UCLASS()
class THEHERO_API UMainMenuUserWidget : public UUserWidget
{
	GENERATED_BODY()
private:
	class ATP_RollingGameMode* RollingGameMode;
	class UTheHeroInstance* TheHeroInstance;

	UFUNCTION()
		void OnBtnSelLoginClicked();
	UFUNCTION()
		void OnBtnSelCadastroClicked();
	UFUNCTION()
		void OnBtnSelSetupClicked();
	UFUNCTION()
		void OnIniciarPartidaClicked();
	UFUNCTION()
		void OnBtnSairClicked();
	UFUNCTION()
		void OnBtnCadastrarClicked();

	UFUNCTION()
		void OnLoginSuccess(int Id, FString Login, FString Token, FString SuccessMessage);
	UFUNCTION()
		void OnLoginError(FString ErrorMessage);

	UFUNCTION()
		void OnCadastroSuccess(int Id, FString Login, FString SuccessMessage);

	UFUNCTION()
		void OnCadastroError(FString ErrorMessage);

	UFUNCTION()
		void ChangePageSelection();

	FTimerHandle DelayToChangeSelection;


public:
	UMainMenuUserWidget(const FObjectInitializer& ObjectInitializer);

	// Optionally override the Blueprint "Event Construct" event
	virtual void NativeConstruct() override;

	// Optionally override the tick event
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;


	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		class UWidgetSwitcher* SelectWidgetSwitcher = nullptr;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		class UTextBlock* MensagemErroLogin = nullptr;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		class UTextBlock* MensagemErroCadastro = nullptr;

	/////////////////////////////////////////////////////////
	// SELECAO PAGINA (LOGIN, CADASTRO, SETUP) //
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		class UButton* BtnSelLogin = nullptr;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		class UButton* BtnSelCadastro = nullptr;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		class UButton* BtnSelSetup = nullptr;
	/////////////////////////////////////////////////////////
	// TELA DE LOGIN //
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		class UEditableTextBox* LoginUsuario = nullptr;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		class UEditableTextBox* LoginSenha = nullptr;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		class UButton* BtnIniciarPartida = nullptr;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		class UButton* BtnSair = nullptr;

	/////////////////////////////////////////////////////////
	// TELA DE CADASTRO //
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		class UEditableTextBox* CadastroUsuario = nullptr;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		class UEditableTextBox* CadastroSenha = nullptr;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		class UEditableTextBox* CadastroEmail = nullptr;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		class UButton* BtnCadastrar = nullptr;


};
