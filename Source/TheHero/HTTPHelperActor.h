// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Runtime/Online/HTTP/Public/Http.h"
#include "HTTPHelperActor.generated.h"

UCLASS()
class THEHERO_API AHTTPHelperActor : public AActor
{
	GENERATED_BODY()

public:
	FHttpModule *Http;

	AHTTPHelperActor();

	UFUNCTION(BlueprintCallable)
	void FireHttpCall();

	void OnResponseReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
};
