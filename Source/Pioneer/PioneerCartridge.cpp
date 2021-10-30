#include "PioneerCartridge.h"
#include <string>

void UPioneerCartridge::BeginPlay()
{
    Super::BeginPlay();

    InitialiseGame();
}

void UPioneerCartridge::OnInput(const FString &Input)
{
    const TCHAR *format = TEXT("Attempts left: %i");
    FString message = FString::Printf(format, this->NumberOfAttemptsLeft);
    PrintLine(message);

    if (!this->bGameHasEnded && this->NumberOfAttemptsLeft == 0)
    {
        return this->EndGame();
    }

    if (this->bGameHasEnded)
    {
        return InitialiseGame();
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

    const TCHAR *format = TEXT("Nice! The answer is %s");
    FString message = FString::Printf(format, *this->Secret);
    PrintLine(message);
}

void UPioneerCartridge::HandleInvalidGuess(FString validationMessage)
{
    PrintLine(validationMessage);

    this->NumberOfAttemptsLeft--;

    if (this->NumberOfAttemptsLeft < 0)
    {
        return this->EndGame();
    }

    const TCHAR *format = TEXT("Attempts left: %i");
    FString message = FString::Printf(format, this->NumberOfAttemptsLeft);
    PrintLine(message);
}

void UPioneerCartridge::InitialiseGame()
{
    this->bGameHasEnded = false;
    this->Secret = TEXT("Pioneer");
    this->ResetAttempts();

    PrintLine(TEXT("What was the name of the first failed probe launched to the moon by man?"));
    PrintLine(TEXT("Press 'Tab' to interact."));
}

FString UPioneerCartridge::ValidateGuess(FString Guess)
{
    const uint8 secret_length = this->Secret.Len();

    if (Guess.Len() != secret_length)
    {
        const TCHAR *format = TEXT("Invalid length. Hint: length is %i");
        return FString::Printf(format, secret_length);
    }

    return {};
}

void UPioneerCartridge::EndGame()
{
    this->bGameHasEnded = true;
    PrintLine(TEXT("No attempts left."));
    PrintLine(TEXT("Press enter to start a new one."));
}

void UPioneerCartridge::ResetAttempts()
{
    this->NumberOfAttemptsLeft = this->Secret.Len();
}