// Copyright LiberiumProject. All Rights Reserved.

#include "LiberiumGameModeBase.h"
#include "LiberiumProjrct/Core/GameInstance/LiberiumGameInstance.h"

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
