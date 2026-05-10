// Copyright LiberiumProject. All Rights Reserved.

#include "LiberiumProjrct/Core/GameMode/LiberiumDungeonGameMode.h"
#include "LiberiumProjrct/Core/GameInstance/LiberiumGameInstance.h"
#include "LiberiumProjrct/Core/LiberiumGameTypes.h"

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
