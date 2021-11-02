#include "PioneerCartridge.h"
#include <string>

void UPioneerCartridge::BeginPlay()
{
    Super::BeginPlay();

    InitialiseGame();
}

void UPioneerCartridge::OnInput(const FString &user_input)
{
    PrintLine(TEXT("Attempts left: %i"), this->NumberOfAttemptsLeft);

    if (!this->bGameHasEnded && this->NumberOfAttemptsLeft == 0)
    {
        return this->EndGame();
    }

    if (this->bGameHasEnded)
    {
        return InitialiseGame();
    }

    return UPioneerCartridge::HandleGuess(user_input);
}

void UPioneerCartridge::HandleGuess(FString user_input_guess)
{
    const FString validationMessage = this->ValidateGuess(user_input_guess);

    ClearScreen();
    PrintLine(user_input_guess);

    if (!validationMessage.IsEmpty())
    {
        this->HandleInvalidGuess(validationMessage);
        return;
    }

    this->ResetAttempts();

    PrintLine(TEXT("Nice! The answer is %s"), *this->Secret);
}

void UPioneerCartridge::HandleInvalidGuess(FString validationMessage)
{
    PrintLine(validationMessage);

    this->NumberOfAttemptsLeft--;

    if (this->NumberOfAttemptsLeft < 0)
    {
        return this->EndGame();
    }

    PrintLine(TEXT("Attempts left: %i"), this->NumberOfAttemptsLeft);

    this->PrintHints();
}

void UPioneerCartridge::InitialiseGame()
{
    this->bGameHasEnded = false;
    this->Secret = TEXT("Pioneer");
    this->ResetAttempts();

    PrintLine(TEXT("What was the name of the first failed probe launched to the moon by man?"));
    PrintLine(TEXT("Press 'Tab' to interact."));

    this->PrintHints();
}

void UPioneerCartridge::PrintHints() const
{
    PrintLine(TEXT("Hint: first character is %c"), this->Secret[0]);
    PrintLine(TEXT("Hint: third character is %c"), this->Secret[2]);
}

FString UPioneerCartridge::ValidateGuess(FString user_input_guess) const
{
    const FString secret = this->Secret;
    const uint8 secret_length = secret.Len();

    if (user_input_guess == secret)
    {
        return {};
    }

    if (user_input_guess.Len() != secret_length)
    {
        return FString::Printf(TEXT("Invalid length."));
    }

    TCHAR *format;
    FString message;
    bool isValidCharacter;

    for (int index = 0; index < secret.Len(); index++)
    {
        isValidCharacter = user_input_guess[index] == secret[index];

        if (isValidCharacter)
        {
            continue;
        }

        format = TEXT("Invalid character at position %i\n");
        message += FString::Printf(format, index);
    }

    return message;
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