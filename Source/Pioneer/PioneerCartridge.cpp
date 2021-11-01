#include "PioneerCartridge.h"
#include <string>

void UPioneerCartridge::BeginPlay()
{
    Super::BeginPlay();

    InitialiseGame();
}

void UPioneerCartridge::OnInput(const FString &user_input)
{
    const TCHAR format[] = TEXT("Attempts left: %i");
    const FString message = FString::Printf(format, this->NumberOfAttemptsLeft);
    PrintLine(message);

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

    const TCHAR format[] = TEXT("Nice! The answer is %s");
    const FString message = FString::Printf(format, *this->Secret);
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

    const TCHAR format[] = TEXT("Attempts left: %i");
    const FString message = FString::Printf(format, this->NumberOfAttemptsLeft);
    PrintLine(message);

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

void UPioneerCartridge::PrintHints()
{
    const TCHAR first_hint_format[] = TEXT("Hint: first character is %c");
    FString message = FString::Printf(first_hint_format, this->Secret[0]);

    const TCHAR second_hint_format[] = TEXT("\nHint: third character is %c");
    message += FString::Printf(second_hint_format, this->Secret[2]);
    PrintLine(message);
}

FString UPioneerCartridge::ValidateGuess(FString user_input_guess)
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