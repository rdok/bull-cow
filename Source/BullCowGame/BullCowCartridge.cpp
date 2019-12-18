#include "BullCowCartridge.h"
#include <string>

void UBullCowCartridge::BeginPlay()
{
    Super::BeginPlay();

    SetupGuessParams();

    PrintWelcomeMessage();
}

void UBullCowCartridge::OnInput(const FString &Guess)
{
    FString validationMessage = this->ValidateGuess(Guess);

    ClearScreen();
    PrintLine(Guess);

    if(! validationMessage.IsEmpty()) {
        this->handleInvalidGuess(validationMessage);
        return;
    }

    FString message = FString::Printf(
        TEXT("Nice! Indeed, the answer is %s"),
        *this->Secret
    );

    PrintLine(message);
}

void UBullCowCartridge::handleInvalidGuess(FString validationMessage) {

    PrintLine(validationMessage);

    this->Attempts--;

    FString message = FString::Printf(
        TEXT("Attempts left: %i"),
        this->Attempts
    );

    PrintLine(message);
}

void UBullCowCartridge::SetupGuessParams()
{
    this->Secret = "Pioneer";
    this->Attempts = 3;
}

FString UBullCowCartridge::ValidateGuess(FString Guess)
{
    const int32 secretLength = this->Secret.Len();

    if (Guess.Len() != secretLength)
    {
        return FString::Printf(
            TEXT("Invalid length. Hint: length is %i"),
            secretLength
        );
    }

    return {};
}

void  UBullCowCartridge::PrintWelcomeMessage() {
    PrintLine(TEXT("What was the name of the first failed probe launched to the moon by man?"));
}