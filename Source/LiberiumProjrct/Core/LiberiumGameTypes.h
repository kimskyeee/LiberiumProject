// Copyright LiberiumProject. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "LiberiumGameTypes.generated.h"

UENUM(BlueprintType)
enum class EGamePhase : uint8
{
	None		UMETA(DisplayName = "None"),
	Town		UMETA(DisplayName = "Town"),
	Dungeon		UMETA(DisplayName = "Dungeon"),
	Combat		UMETA(DisplayName = "Combat"),
	Minigame	UMETA(DisplayName = "Minigame")
};
