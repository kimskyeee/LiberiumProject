// Copyright LiberiumProject. All Rights Reserved.

#include "Core/GameMode/LiberiumDungeonGameMode.h"
#include "Core/GameInstance/LiberiumGameInstance.h"
#include "Core/LiberiumGameTypes.h"

ALiberiumDungeonGameMode::ALiberiumDungeonGameMode()
{
}

void ALiberiumDungeonGameMode::BeginPlay()
{
	Super::BeginPlay();

	if (ULiberiumGameInstance* GI = GetLiberiumGameInstance())
	{
		GI->SetGamePhase(EGamePhase::Dungeon);
	}
}
