#include "TP_RollingGameMode.h"
#include "TP_RollingBall.h"
#include "Kismet/GameplayStatics.h"
#include "Components/AudioComponent.h"
#include "TheHero/TheHeroInstance.h"
#include "GameFramework/PlayerController.h"
#include "Components/StaticMeshComponent.h"
#include "TimerManager.h"
#include "TheHero/PassarelaCreator.h"
#include "Components/AudioComponent.h"

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
	static ConstructorHelpers::FObjectFinder<USoundBase> SOUND_GAME_THEME_PLAY(TEXT("/Game/Audio/game-theme_Cue"));


	//static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/RollingCPP/Blueprint/TP_RollingBallPlayer"));

	AudioGameOver = CreateDefaultSubobject<UAudioComponent>(TEXT("AudioGameOver"));
	AudioGameOver->SetupAttachment(RootComponent);
	AudioGameOver->SetAutoActivate(false);

	AudioGameThemeDuringPlay = CreateDefaultSubobject<UAudioComponent>(TEXT("AudioGameThemeDuringPlay"));
	AudioGameThemeDuringPlay->SetupAttachment(RootComponent);
	AudioGameThemeDuringPlay->SetAutoActivate(false);


	DefaultPawnClass = ATP_RollingBall::StaticClass();

	if (SOUND_GAME_OVER.Object != nullptr)
	{
		AudioGameOver->SetSound(SOUND_GAME_OVER.Object);
	}

	if (SOUND_GAME_THEME_PLAY.Object != nullptr) {
		AudioGameThemeDuringPlay->SetSound(SOUND_GAME_THEME_PLAY.Object);
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
		AudioGameThemeDuringPlay->Play();

		CurrentGameInstance = Cast<UTheHeroInstance>(GI);

		CurrentGameInstance->PlayerIsDead = false;
		CurrentGameInstance->RecuperarRankingGlobal();

		auto Passarela = Cast<APassarelaCreator>(UGameplayStatics::GetActorOfClass(GetWorld(), APassarelaCreator::StaticClass()));
		if (Passarela != nullptr)
		{
			Passarela->OnPlayerDiedNow.AddDynamic(this, &ATP_RollingGameMode::OnPlayerDiedNow);
		}

		auto PC = GetWorld()->GetFirstPlayerController();
		if (PC != nullptr) {

			auto PP = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
			if (PP) {
				ATP_RollingBall* RollPP = Cast<ATP_RollingBall>(PP);
				RollPP->ExecuteEmitterAtBegin();
			}
		}


		GetWorld()->GetTimerManager().SetTimer(GameTimeTimerHandle, this, &ATP_RollingGameMode::CountGameTime, 1, true, 1.0f);
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
		CurrentGameInstance->DoRegisterLastPlayedGame();
		CurrentGameInstance->ResetPlayerValues(0);

		AudioGameThemeDuringPlay->Stop();

		AudioGameOver->Play();

		auto PC = GetWorld()->GetFirstPlayerController();
		if (PC != nullptr) {

			auto PP = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
			if (PP) {
				ATP_RollingBall* RollPP = Cast<ATP_RollingBall>(PP);
				auto base_comp = Cast<UStaticMeshComponent>(RollPP->GetRootComponent());
				if (base_comp) {
					base_comp->SetSimulatePhysics(false);
				}
				RollPP->DisableInput(PC);
				RollPP->ExecuteEmitterAtDeath();
			}
		}

		GetWorld()->GetTimerManager().ClearTimer(GameTimeTimerHandle);
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

void ATP_RollingGameMode::CountGameTime()
{
	auto GI = GetGameInstance();
	if (GI != nullptr)
	{
		CurrentGameInstance = Cast<UTheHeroInstance>(GI);
		if (!CurrentGameInstance->PlayerIsDead) {
			CurrentGameInstance->UpdatePlayerTime(1);
		}

	}
}
