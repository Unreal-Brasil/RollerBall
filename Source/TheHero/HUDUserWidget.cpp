#include "HUDUserWidget.h"
#include "Components/TextBlock.h"
#include "Components/SlateWrapperTypes.h"
#include "Kismet/GameplayStatics.h"
#include "TP_Rolling/TP_RollingGameMode.h"
#include "TheHeroInstance.h"

UHUDUserWidget::UHUDUserWidget(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer)
{

}

void UHUDUserWidget::NativeConstruct()
{
    Super::NativeConstruct();

    if (ScoreIncrement)
        ScoreIncrement->SetText(FText::FromString("0"));

    if (UserLogin)
        UserLogin->SetText(FText::FromString("##"));

    if (PlayerTime)
        PlayerTime->SetText(FText::FromString("0"));

    if (CountDownToRestart) {
        CountDownToRestart->SetText(FText::FromString("0"));
        CountDownToRestart->SetVisibility(ESlateVisibility::Hidden);
    }

    auto GM = UGameplayStatics::GetGameMode(GetWorld());
    if (GM) {
        RollingGameMode = Cast<ATP_RollingGameMode>(GM);
        RollingGameMode->OnCountDownToRestart.AddDynamic(this, &UHUDUserWidget::OnCountDownUpdate);
    }

    auto GI = UGameplayStatics::GetGameInstance(GetWorld());
    if (GI)
    {
        TheHeroInstance = Cast<UTheHeroInstance>(GI);
    }
}

void UHUDUserWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
    Super::NativeTick(MyGeometry, InDeltaTime);

    if (TheHeroInstance != nullptr) {
        PlayerTime->SetText(FText::FromString(FString::FromInt(TheHeroInstance->PlayerTime)));
        ScoreIncrement->SetText(FText::FromString(FString::FromInt(TheHeroInstance->PlayerScore)));
        UserLogin->SetText(FText::FromString(TheHeroInstance->PlayerLogin));
    }
}

void UHUDUserWidget::OnCountDownUpdate(int Counter)
{
    if (CountDownToRestart) {
        FString StrCounter = FString::FromInt(Counter);
        CountDownToRestart->SetVisibility(ESlateVisibility::Visible);
        CountDownToRestart->SetText(FText::FromString(StrCounter));
    }
}
