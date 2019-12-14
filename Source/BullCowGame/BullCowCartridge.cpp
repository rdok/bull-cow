// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h"

void UBullCowCartridge::BeginPlay() // When the game starts
{
    Super::BeginPlay();

    PrintLine("Pioneer, the first satellite launched.");
    PrintLine("What was the launch year of Pioneer probe?");
}

void UBullCowCartridge::OnInput(const FString& Input) // When the player hits enter
{
    FString Isogram = "spacecraft";

    ClearScreen();
}