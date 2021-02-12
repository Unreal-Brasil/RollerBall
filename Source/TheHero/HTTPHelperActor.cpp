// Fill out your copyright notice in the Description page of Project Settings.


#include "HTTPHelperActor.h"


// Sets default values
AHTTPHelperActor::AHTTPHelperActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	Http = &FHttpModule::Get();

}

void AHTTPHelperActor::FireHttpCall()
{
	auto Request = Http->CreateRequest();
	Request->OnProcessRequestComplete().BindUObject(this, &AHTTPHelperActor::OnResponseReceived);
	//This is the url on which to process the request
	Request->SetURL("http://localhost:3000/user");
	Request->SetVerb("GET");
	Request->SetHeader(TEXT("User-Agent"), "X-UnrealEngine-Agent");
	Request->SetHeader("Content-Type", TEXT("application/json"));
	Request->ProcessRequest();
}

void AHTTPHelperActor::OnResponseReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful)
{
	//Create a pointer to hold the json serialized data
	TSharedPtr<FJsonObject> JsonObject;

	//Create a reader pointer to read the json data
	TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(Response->GetContentAsString());

	//Deserialize the json data given Reader and the actual object to deserialize
	if (FJsonSerializer::Deserialize(Reader, JsonObject))
	{
		//Get the value of the json object by field name
		FString recievedVal = JsonObject->GetStringField("status");

		//Output it to the engine
		GEngine->AddOnScreenDebugMessage(1, 2.0f, FColor::Green, recievedVal);
	}
}

// Called when the game starts or when spawned
void AHTTPHelperActor::BeginPlay()
{
	Super::BeginPlay();
	FireHttpCall();

}


