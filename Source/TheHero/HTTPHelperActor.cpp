// Fill out your copyright notice in the Description page of Project Settings.


#include "HTTPHelperActor.h"


AHTTPHelperActor::AHTTPHelperActor()
{
	PrimaryActorTick.bCanEverTick = false;
	Http = &FHttpModule::Get();

}

void AHTTPHelperActor::FireHttpCall()
{
	auto Request = Http->CreateRequest();
	Request->OnProcessRequestComplete().BindUObject(this, &AHTTPHelperActor::OnResponseReceived);
	Request->SetURL("http://localhost:3000/user");
	Request->SetVerb("GET");
	Request->SetHeader(TEXT("User-Agent"), "X-UnrealEngine-Agent");
	Request->SetHeader("Content-Type", TEXT("application/json"));
	Request->ProcessRequest();
}

void AHTTPHelperActor::OnResponseReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful)
{

	TSharedPtr<FJsonObject> JsonObject;
	TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(Response->GetContentAsString());

	if (FJsonSerializer::Deserialize(Reader, JsonObject))
	{
		FString recievedVal = JsonObject->GetStringField("status");
		GEngine->AddOnScreenDebugMessage(1, 2.0f, FColor::Green, recievedVal);
	}
}

void AHTTPHelperActor::BeginPlay()
{
	Super::BeginPlay();
	FireHttpCall();
}


