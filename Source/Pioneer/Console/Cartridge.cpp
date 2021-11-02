#include "Cartridge.h"
#include "Terminal.h"
#include "GameFramework/Actor.h"
#include "Misc/Paths.h"
#include "Misc/FileHelper.h"

void UCartridge::BeginPlay()
{
	Super::BeginPlay();

	const FString secrets_file_name = FPaths::ProjectContentDir() / TEXT("secrets.txt");
	FFileHelper::LoadFileToStringArray(Secrets, *secrets_file_name);

	Terminal = GetOwner()->FindComponentByClass<UTerminal>();
	checkf(Terminal, TEXT("[%s]: No Terminal found"), *GetName())
}

void UCartridge::PrintLine(const FString &Line) const
{
	Terminal->PrintLine(Line);
}

void UCartridge::PrintLine(const TCHAR *Line) const
{
	Terminal->PrintLine(Line);
}

void UCartridge::ClearScreen() const
{
	Terminal->ClearScreen();
}
