// Copyright LiberiumProject. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "MinigameResult.generated.h"

USTRUCT(BlueprintType)
struct FMinigameResult
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, Category = "Result")
	FText GameName;

	UPROPERTY(BlueprintReadOnly, Category = "Result")
	int32 Score = 0;

	UPROPERTY(BlueprintReadOnly, Category = "Result")
	TMap<FString, FText> ExtraFields;

	UPROPERTY(BlueprintReadOnly, Category = "Result")
	bool bNewHighScore = false;
};
