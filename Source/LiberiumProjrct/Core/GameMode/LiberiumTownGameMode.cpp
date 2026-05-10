// Copyright LiberiumProject. All Rights Reserved.

#include "LiberiumProjrct/Core/GameMode/LiberiumTownGameMode.h"
#include "LiberiumProjrct/Core/GameInstance/LiberiumGameInstance.h"
#include "LiberiumProjrct/Core/LiberiumGameTypes.h"

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
