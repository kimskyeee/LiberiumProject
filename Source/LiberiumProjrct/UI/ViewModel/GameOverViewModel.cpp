// Copyright LiberiumProject. All Rights Reserved.

#include "UI/ViewModel/GameOverViewModel.h"

void UGameOverViewModel::SetResult(const FMinigameResult& InResult)
{
	Result = InResult;
	BroadcastUpdate();
}
