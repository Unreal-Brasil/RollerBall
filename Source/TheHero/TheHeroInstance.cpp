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
    Request->SetURL("http://localhost:3000/dologin");
    Request->SetVerb("POST");
    Request->SetHeader(TEXT("User-Agent"), "X-UnrealEngine-Agent");
    Request->SetHeader("Content-Type", TEXT("application/json"));

    FString Payload = FString::Printf(TEXT("{ \"userName\": \"%s\", \"password\":\"%s\"}"), *UserName, *Password);

    UE_LOG(LogTemp, Warning, TEXT("%s"), *Payload);

    Request->SetContentAsString(Payload);

    Request->ProcessRequest();
}

void UTheHeroInstance::DoCadastro(FString UserName, FString Password, FString Email)
{
    // BENZADEUS!!!!
    auto Request = Http->CreateRequest();
    Request->OnProcessRequestComplete().BindUObject(this, &UTheHeroInstance::OnCadastroResponseReceived);
    Request->SetURL("http://localhost:3000/doregister");
    Request->SetVerb("POST");
    Request->SetHeader(TEXT("User-Agent"), "X-UnrealEngine-Agent");
    Request->SetHeader("Content-Type", TEXT("application/json"));

    FString Payload = FString::Printf(TEXT("{ \"userName\": \"%s\", \"password\":\"%s\", \"email\":\"%s\", \"habilitado\":true}"), *UserName, *Password, *Email);

    UE_LOG(LogTemp, Warning, TEXT("%s"), *Payload);

    Request->SetContentAsString(Payload);

    Request->ProcessRequest();
}

void UTheHeroInstance::DoRegisterLastPlayedGame()
{
    auto Request = Http->CreateRequest();
    Request->SetURL("http://localhost:3000/doregistergame");
    Request->SetVerb("POST");
    Request->SetHeader(TEXT("User-Agent"), "X-UnrealEngine-Agent");
    Request->SetHeader("Content-Type", TEXT("application/json"));

    FString Payload = FString::Printf(TEXT("{ \"token\": \"%s\", \"score\":%d, \"time\":%d }"), *Token, PlayerScore, PlayerTime);

    UE_LOG(LogTemp, Warning, TEXT("%s"), *Payload);

    Request->SetContentAsString(Payload);

    Request->ProcessRequest();

}

void UTheHeroInstance::RecuperarRankingGlobal()
{
    auto Request = Http->CreateRequest();
    Request->OnProcessRequestComplete().BindUObject(this, &UTheHeroInstance::OnRankingGlobalResponseReceived);
    Request->SetURL("http://localhost:3000/getrankingglobal");
    Request->SetVerb("POST");
    Request->SetHeader(TEXT("User-Agent"), "X-UnrealEngine-Agent");
    Request->SetHeader("Content-Type", TEXT("application/json"));

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
                Token = JsonObject->GetStringField("token");
                OnLoginResultSuccess.Broadcast(PlayerId, PlayerLogin, Token, Mensagem);
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
    else
    {
        OnLoginResultError.Broadcast("Ocorreu um erro inesperado!");
    }
}

void UTheHeroInstance::OnCadastroResponseReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful)
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
                OnCadastroReultSuccess.Broadcast(PlayerId, PlayerLogin, Mensagem);
            }
            else
            {
                FString msg_error = JsonObject->GetStringField("mensagem");
                OnCadastroReultError.Broadcast(msg_error);
            }

            //Joga na tela.
            GEngine->AddOnScreenDebugMessage(1, 2.0f, FColor::Green, Mensagem);
        }
    }
}

void UTheHeroInstance::OnRankingGlobalResponseReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful)
{
    if (bWasSuccessful)
    {
        UE_LOG(LogTemp, Warning, TEXT("%s"), *Response->GetContentAsString());

        RankingList.Empty();
        //Cria um ponteiro para armazenar os dados singelos.
        TSharedPtr<FJsonObject> JsonObject;

        //Cria um ponteiro de leitura para ler os dados do json.
        TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(Response->GetContentAsString());

        // Deserializa os bagulhos.
        if (FJsonSerializer::Deserialize(Reader, JsonObject))
        {
            auto list_ranking = JsonObject->GetArrayField("ranking");

            for (int w = 0;w < list_ranking.Num();w++) {
                FRankingItemUserData ud = FRankingItemUserData();

                const TSharedPtr<FJsonObject>* objrow;

                bool result_get = list_ranking[w]->TryGetObject(objrow);

                if (result_get) {
                    ud.PosicaoRanking = FString::FromInt(w + 1);
                    ud.LoginUsuario = objrow->Get()->GetStringField("userName");
                    ud.PontuacaoUsuario = objrow->Get()->GetStringField("maxScore");
                    RankingList.Add(ud);
                }
            }


            if (RankingList.Num() > 0) {
                OnRecuperarRankingGlobalResultSuccess.Broadcast(RankingList);
            }
            else {
                OnRecuperarRankingGlobalResultError.Broadcast("Nenhuma informação recuperada!");
            }
        }
    }

}

UTheHeroInstance::UTheHeroInstance()
{
    Http = &FHttpModule::Get();
}
