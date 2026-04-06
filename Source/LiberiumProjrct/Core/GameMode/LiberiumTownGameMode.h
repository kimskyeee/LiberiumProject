// Copyright LiberiumProject. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Core/GameMode/LiberiumGameModeBase.h"
#include "LiberiumTownGameMode.generated.h"

UCLASS()
class LIBERIUMPROJRCT_API ALiberiumTownGameMode : public ALiberiumGameModeBase
{
	GENERATED_BODY()

public:
	ALiberiumTownGameMode();

protected:
	virtual void BeginPlay() override;
};
