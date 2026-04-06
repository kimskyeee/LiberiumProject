// Copyright LiberiumProject. All Rights Reserved.

#include "Core/GameMode/LiberiumTownGameMode.h"
#include "Core/GameInstance/LiberiumGameInstance.h"
#include "Core/LiberiumGameTypes.h"

ALiberiumTownGameMode::ALiberiumTownGameMode()
{
}

void ALiberiumTownGameMode::BeginPlay()
{
	Super::BeginPlay();

	if (ULiberiumGameInstance* GI = GetLiberiumGameInstance())
	{
		GI->SetGamePhase(EGamePhase::Town);
	}
}
