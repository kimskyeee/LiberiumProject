// Copyright LiberiumProject. All Rights Reserved.

#include "Core/GameMode/LiberiumGameModeBase.h"
#include "Core/GameInstance/LiberiumGameInstance.h"

ALiberiumGameModeBase::ALiberiumGameModeBase()
{
}

void ALiberiumGameModeBase::BeginPlay()
{
	Super::BeginPlay();
}

ULiberiumGameInstance* ALiberiumGameModeBase::GetLiberiumGameInstance() const
{
	return Cast<ULiberiumGameInstance>(GetGameInstance());
}
