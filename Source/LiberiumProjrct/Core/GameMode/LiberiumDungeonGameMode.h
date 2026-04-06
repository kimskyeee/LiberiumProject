// Copyright LiberiumProject. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Core/GameMode/LiberiumGameModeBase.h"
#include "LiberiumDungeonGameMode.generated.h"

UCLASS()
class LIBERIUMPROJRCT_API ALiberiumDungeonGameMode : public ALiberiumGameModeBase
{
	GENERATED_BODY()

public:
	ALiberiumDungeonGameMode();

protected:
	virtual void BeginPlay() override;
};
