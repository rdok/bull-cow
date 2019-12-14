// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h"
#include <string>

void UBullCowCartridge::BeginPlay() // When the game starts
{
    Super::BeginPlay();

    PrintLine(TEXT("Pioneer, the first satellite launched."));
    PrintLine(TEXT("What was the launch year of Pioneer probe?"));
}

void UBullCowCartridge::OnInput(const FString& Input) // When the player hits enter
{
    FString Isogram = TEXT("spacecraft");

    ClearScreen();
    PrintLine(Input);

    FString message = Input == Isogram 
        ? TEXT("correct")
        : TEXT("incorrect");

    PrintLine(message);
}