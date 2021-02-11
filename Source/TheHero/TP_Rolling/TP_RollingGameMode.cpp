#include "TP_RollingGameMode.h"
#include "TP_RollingBall.h"
#include "Kismet/GameplayStatics.h"
#include "TheHero/TheHeroInstance.h"
#include "TheHero/PassarelaCreator.h"

/**
 * 
 * Construtor da classe.
 * 
*/
ATP_RollingGameMode::ATP_RollingGameMode()
{
	PrimaryActorTick.bCanEverTick = true;

	IsClosed = false;

	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/RollingCPP/Blueprint/TP_RollingBallPlayer"));
	if (PlayerPawnBPClass.Class != nullptr)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
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
		UGameplayStatics::OpenLevel(GetWorld(), "L1");
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
