#include "BullCowCartridge.h"

void UBullCowCartridge::BeginPlay()
{
    Super::BeginPlay();

    PrintLine(TEXT("Pioneer, the first satellite launched."));
    PrintLine(TEXT("What was the launch year of Pioneer probe?"));

    InitGuessParams();
}

void UBullCowCartridge::OnInput(const FString &Input)
{
    FString response = this->GetIsogramValidationMessage(Input);

    ClearScreen();
    PrintLine(Input);
    PrintLine(response);
}

void UBullCowCartridge::InitGuessParams()
{
    this->IsoGram = "spacecraft";
    this->Attempts = 3;
}

FString UBullCowCartridge::GetIsogramValidationMessage(FString Input)
{
    return Input == IsoGram ? TEXT("correct") : TEXT("incorrect");
};