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
