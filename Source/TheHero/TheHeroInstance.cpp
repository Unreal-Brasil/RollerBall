#include "TheHeroInstance.h"

void UTheHeroInstance::UpdatePlayerScore(int valor)
{
    PlayerScore += valor;
}

void UTheHeroInstance::UpdatePlayerTime(int valor)
{
    PlayerTime += valor;
}

void UTheHeroInstance::ResetPlayerValues(int valor)
{
    PlayerScore = 0;
    PlayerTime = 0;
}

void UTheHeroInstance::DoLogin(FString UserName, FString Password)
{
    // BENZADEUS!!!!
    auto Request = Http->CreateRequest();
    Request->OnProcessRequestComplete().BindUObject(this, &UTheHeroInstance::OnLoginResponseReceived);
    Request->SetURL("http://localhost:3000/user");
    Request->SetVerb("POST");
    Request->SetHeader(TEXT("User-Agent"), "X-UnrealEngine-Agent");
    Request->SetHeader("Content-Type", TEXT("application/json"));

    const FString Payload("{ \"userName\": \"" + UserName + "\", \"password\":\"" + Password + "\"}");

    UE_LOG(LogTemp, Warning, TEXT("%s"), *Payload);

    Request->SetContentAsString(Payload);

    Request->ProcessRequest();
}

void UTheHeroInstance::OnLoginResponseReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful)
{
    if (bWasSuccessful)
    {
        UE_LOG(LogTemp, Warning, TEXT("%s"), *Response->GetContentAsString());

        //Cria um ponteiro para armazenar os dados singelos.
        TSharedPtr<FJsonObject> JsonObject;

        //Cria um ponteiro de leitura para ler os dados do json.
        TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(Response->GetContentAsString());

        // Deserializa os bagulhos.
        if (FJsonSerializer::Deserialize(Reader, JsonObject))
        {
            //Pega o Status
            FString status = JsonObject->GetStringField("status");

            if (status.Equals("OK"))
            {
                PlayerId = JsonObject->GetIntegerField("id");
                PlayerLogin = JsonObject->GetStringField("username");
                Mensagem = JsonObject->GetStringField("mensagem");
                OnLoginResultSuccess.Broadcast(PlayerId, PlayerLogin, Mensagem);
            }
            else
            {
                FString msg_error = JsonObject->GetStringField("mensagem");
                OnLoginResultError.Broadcast(msg_error);
            }

            //Joga na tela.
            GEngine->AddOnScreenDebugMessage(1, 2.0f, FColor::Green, Mensagem);
        }
    }
}

UTheHeroInstance::UTheHeroInstance()
{
    Http = &FHttpModule::Get();
}
