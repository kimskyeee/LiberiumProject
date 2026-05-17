// Copyright LiberiumProject. All Rights Reserved.

#include "UI/ViewModel/PauseMenuViewModel.h"
#include "Kismet/GameplayStatics.h"

void UPauseMenuViewModel::TogglePause()
{
	bIsPaused = !bIsPaused;

	if (WorldContext.IsValid())
	{
		UGameplayStatics::SetGamePaused(WorldContext.Get(), bIsPaused);
	}

	BroadcastUpdate();
}

void UPauseMenuViewModel::ResumeGame()
{
	bIsPaused = false;

	if (WorldContext.IsValid())
	{
		UGameplayStatics::SetGamePaused(WorldContext.Get(), false);
	}

	BroadcastUpdate();
}

void UPauseMenuViewModel::QuitToTown()
{
	ResumeGame();

	if (WorldContext.IsValid())
	{
		// TODO: Travel to town map via GameInstance
		UE_LOG(LogTemp, Log, TEXT("QuitToTown called - implement map travel"));
	}
}
