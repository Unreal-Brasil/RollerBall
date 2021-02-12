#include "TP_RollingGameMode.h"
#include "TP_RollingBall.h"
#include "Kismet/GameplayStatics.h"
#include "Components/AudioComponent.h"
#include "TheHero/TheHeroInstance.h"
#include "GameFramework/PlayerController.h"
#include "TheHero/PassarelaCreator.h"

/**
 * 
 * Construtor da classe.
 * 
*/
ATP_RollingGameMode::ATP_RollingGameMode()
{
	PrimaryActorTick.bCanEverTick = true;
	CountDownToRestart = 3;
	IsClosed = false;
	static ConstructorHelpers::FObjectFinder<USoundBase> SOUND_GAME_OVER(TEXT("/Game/Audio/playgameover_Cue"));
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/RollingCPP/Blueprint/TP_RollingBallPlayer"));

	Audio = CreateDefaultSubobject<UAudioComponent>(TEXT("Audio"));
	Audio->SetupAttachment(RootComponent);
	Audio->SetAutoActivate(false);

	if (PlayerPawnBPClass.Class != nullptr)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}

	if (SOUND_GAME_OVER.Object != nullptr)
	{
		Audio->SetSound(SOUND_GAME_OVER.Object);
	}
}

/**
 * 
 * Evento de início do jogo.
 * 
 */
void ATP_RollingGameMode::BeginPlay()
{
	Super::BeginPlay();
	auto GI = GetGameInstance();
	if (GI != nullptr)
	{
		CurrentGameInstance = Cast<UTheHeroInstance>(GI);
		auto Passarela = Cast<APassarelaCreator>(UGameplayStatics::GetActorOfClass(GetWorld(), APassarelaCreator::StaticClass()));
		if (Passarela != nullptr)
		{
			Passarela->OnPlayerDiedNow.AddDynamic(this, &ATP_RollingGameMode::OnPlayerDiedNow);
		}
	}
}

/**
 * 
 * Evento para reiniciar o jogo. 
 * 
*/
void ATP_RollingGameMode::OnPlayerDiedNow()
{
	if (CurrentGameInstance != nullptr)
	{
		CurrentGameInstance->ResetPlayerValues(0);

		Audio->Play();
		auto PC = GetWorld()->GetFirstPlayerController();

		if (PC != nullptr)
			UGameplayStatics::GetPlayerPawn(GetWorld(), 0)->DisableInput(PC);

		GetWorld()->GetTimerManager().SetTimer(ReloadGameTimerHandle, this, &ATP_RollingGameMode::CountDownToRestartGame, 1, true, 0.0f);
	}
}

/**
 * 
 * Evento de Tick executado a cada quadro do jogo.
 * 
*/
void ATP_RollingGameMode::Tick(float DeltaTime)
{
	if (IsClosed)
		return;

	if (CurrentGameInstance != nullptr)
	{
		const int ptimer = CurrentGameInstance->RetrievePlayerTime();
		const int pscore = CurrentGameInstance->RetrievePlayerScore();

		if (ptimer > 10)
		{
			if (pscore < ptimer)
			{
				OnPlayerDied.Broadcast();
				IsClosed = true;
				OnPlayerDiedNow();
			}
		}
	}
}

void ATP_RollingGameMode::CountDownToRestartGame()
{
	OnCountDownToRestart.Broadcast(CountDownToRestart);
	CountDownToRestart--;

	if (CountDownToRestart < 0)
	{
		UGameplayStatics::OpenLevel(GetWorld(), "L1");
	}
}
