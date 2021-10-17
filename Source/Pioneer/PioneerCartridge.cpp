#include "PioneerCartridge.h"
#include <string>

void UPioneerCartridge::BeginPlay()
{
    Super::BeginPlay();

    SetupGuessingGame();
}

void UPioneerCartridge::OnInput(const FString &Input)
{
    FString message = FString::Printf(TEXT("Attempts left: %i"), this->Attempts);

    PrintLine(message);

    if (!this->GameHasEnded && this->Attempts == 0)
    {
        return this->EndGame();
    }

    if (this->GameHasEnded)
    {
        return SetupGuessingGame();
    }

    return UPioneerCartridge::HandleGuess(Input);
}

void UPioneerCartridge::HandleGuess(FString Guess)
{
    FString validationMessage = this->ValidateGuess(Guess);

    ClearScreen();
    PrintLine(Guess);

    if (!validationMessage.IsEmpty())
    {
        this->HandleInvalidGuess(validationMessage);
        return;
    }

    this->ResetAttempts();

    FString message = FString::Printf(
        TEXT("Nice! Indeed, the answer is %s"),
        *this->Secret);

    PrintLine(message);
}

void UPioneerCartridge::HandleInvalidGuess(FString validationMessage)
{
    PrintLine(validationMessage);

    this->Attempts--;

    if (this->Attempts < 0)
    {
        return this->EndGame();
    }

    FString message = FString::Printf(
        TEXT("Attempts left: %i"),
        this->Attempts);

    PrintLine(message);
}

void UPioneerCartridge::SetupGuessingGame()
{
    this->GameHasEnded = false;
    this->Secret = "Pioneer";
    this->ResetAttempts();

    PrintLine(TEXT("What was the name of the first failed probe launched to the moon by man?"));
}

FString UPioneerCartridge::ValidateGuess(FString Guess)
{
    const int32 secretLength = this->Secret.Len();

    if (Guess.Len() != secretLength)
    {
        return FString::Printf(
            TEXT("Invalid length. Hint: length is %i"),
            secretLength);
    }

    return {};
}

void UPioneerCartridge::EndGame()
{
    this->GameHasEnded = true;
    PrintLine(TEXT("No attempts left."));
    PrintLine(TEXT("Press enter to start a new one."));
}

void UPioneerCartridge::ResetAttempts()
{
    this->Attempts = this->Secret.Len();
}