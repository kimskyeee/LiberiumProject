// Copyright LiberiumProject. All Rights Reserved.

#include "UI/ViewModel/StackGameHUDViewModel.h"
#include "Minigame/StackGame/StackingGameMode.h"

void UStackGameHUDViewModel::Initialize(UWorld* InWorld)
{
	Super::Initialize(InWorld);

	if (!WorldContext.IsValid())
	{
		return;
	}

	if (AStackingGameMode* GM = Cast<AStackingGameMode>(WorldContext->GetAuthGameMode()))
	{
		GM->OnScoreChanged.AddDynamic(this, &UStackGameHUDViewModel::HandleScoreChanged);
		GM->OnGameOverEvent.AddDynamic(this, &UStackGameHUDViewModel::HandleGameOver);
	}
}

void UStackGameHUDViewModel::Deinitialize()
{
	if (WorldContext.IsValid())
	{
		if (AStackingGameMode* GM = Cast<AStackingGameMode>(WorldContext->GetAuthGameMode()))
		{
			GM->OnScoreChanged.RemoveDynamic(this, &UStackGameHUDViewModel::HandleScoreChanged);
			GM->OnGameOverEvent.RemoveDynamic(this, &UStackGameHUDViewModel::HandleGameOver);
		}
	}

	Super::Deinitialize();
}

void UStackGameHUDViewModel::HandleScoreChanged()
{
	if (!WorldContext.IsValid())
	{
		return;
	}

	if (AStackingGameMode* GM = Cast<AStackingGameMode>(WorldContext->GetAuthGameMode()))
	{
		Score = GM->GetScore();
		BlockCount = GM->GetBlockCount();
		BroadcastUpdate();
	}
}

void UStackGameHUDViewModel::HandleGameOver()
{
	bGameOver = true;

	if (WorldContext.IsValid())
	{
		if (AStackingGameMode* GM = Cast<AStackingGameMode>(WorldContext->GetAuthGameMode()))
		{
			Score = GM->GetScore();
			BlockCount = GM->GetBlockCount();
		}
	}

	BroadcastUpdate();
}
