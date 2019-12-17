#include "BullCowCartridge.h"
#include <string>

void UBullCowCartridge::BeginPlay()
{
    Super::BeginPlay();

    PrintLine(TEXT("What was the name of the first failed probe launched to the moon by man?"));

    InitGuessParams();
}

void UBullCowCartridge::OnInput(const FString &Guess)
{
    FString response = this->ValidateGuess(Guess);

    ClearScreen();
    PrintLine(Guess);
    PrintLine(response);
}

void UBullCowCartridge::InitGuessParams()
{
    this->Secret = "Pioneer";
    this->Attempts = 3;
}

FString UBullCowCartridge::ValidateGuess(FString Guess)
{
    const int32 secretLength = this->Secret.Len();

    if (Guess.Len() != secretLength)
    {
        return TEXT("Invalid length. Hint: length is %s", ToText(secretLength));
    }

    return Guess == this->Secret ? TEXT("Correct") : TEXT("Wrong");
}