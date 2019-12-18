// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Console/Cartridge.h"
#include "BullCowCartridge.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class BULLCOWGAME_API UBullCowCartridge : public UCartridge
{

	GENERATED_BODY()

	public:
	void SetupGuessParams();
	void PrintWelcomeMessage();
	void handleInvalidGuess(FString message);

	virtual void BeginPlay() override;
	virtual void OnInput(const FString& Input) override;

	FString ValidateGuess(FString Response);

	private:
	FString Secret;
	int32 Attempts;
};
