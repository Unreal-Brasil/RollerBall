// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "GameFramework/Actor.h"
#include "Runtime/Online/HTTP/Public/Http.h"
#include "TheHeroInstance.generated.h"

/**
 *
 */
UCLASS()
class THEHERO_API UTheHeroInstance : public UGameInstance
{
	GENERATED_BODY()
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FLoginResultSuccessSignature, int, Id, FString, Login,  FString, Token, FString, SuccessMessage);
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FLoginResultErrorSignature, FString, ErrorMessage);
	// -----------------------------------------------------------
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FCadastroResultSuccessSignature, int, Id, FString, Login, FString, SuccessMessage);
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FCadastroResultErrorSignature, FString, ErrorMessage);

private:
	FHttpModule *Http;

	void OnLoginResponseReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful);
	void OnCadastroResponseReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful);
	FString Mensagem;
	FString Token;

public:
	UTheHeroInstance();

	UPROPERTY(BlueprintAssignable)
	FCadastroResultSuccessSignature OnCadastroReultSuccess;

	UPROPERTY(BlueprintAssignable)
	FCadastroResultErrorSignature OnCadastroReultError;

	UPROPERTY(BlueprintAssignable)
	FLoginResultSuccessSignature OnLoginResultSuccess;

	UPROPERTY(BlueprintAssignable)
	FLoginResultErrorSignature OnLoginResultError;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "PlayerScore")
	int PlayerScore;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "PlayerScore")
	int PlayerTime;

	UPROPERTY(EditDefaultsOnly, BlueprintReadonly, Category = "PlayerLogin")
	int PlayerId;

	UPROPERTY(EditDefaultsOnly, BlueprintReadonly, Category = "PlayerLogin")
	FString PlayerLogin;

	/////////////////////////////////////////////////////////////////////
	UFUNCTION(BlueprintCallable)
	void DoLogin(FString UserName, FString Password);
	/////////////////////////////////////////////////////////////////////
	UFUNCTION(BlueprintCallable)
	void DoCadastro(FString UserName, FString Password, FString Email);

	UFUNCTION(BlueprintCallable)
	void ResetPlayerValues(int valor);

	UFUNCTION(BlueprintCallable)
	void UpdatePlayerScore(int valor);

	UFUNCTION(BlueprintCallable)
	FORCEINLINE int RetrievePlayerScore() const { return PlayerScore; };

	UFUNCTION(BlueprintCallable)
	void UpdatePlayerTime(int valor);

	UFUNCTION(BlueprintCallable)
	FORCEINLINE int RetrievePlayerTime() const { return PlayerTime; };
};
