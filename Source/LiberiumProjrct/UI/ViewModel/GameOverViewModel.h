// Copyright LiberiumProject. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "LiberiumProjrct/UI/ViewModel/LiberiumViewModelBase.h"
#include "LiberiumProjrct/UI/Model/MinigameResult.h"
#include "GameOverViewModel.generated.h"

UCLASS(BlueprintType)
class LIBERIUMPROJRCT_API UGameOverViewModel : public ULiberiumViewModelBase
{
	GENERATED_BODY()

public:
	void SetResult(const FMinigameResult& InResult);

	UFUNCTION(BlueprintCallable, Category = "GameOver")
	const FMinigameResult& GetResult() const { return Result; }

	UFUNCTION(BlueprintCallable, Category = "GameOver")
	FText GetGameName() const { return Result.GameName; }

	UFUNCTION(BlueprintCallable, Category = "GameOver")
	int32 GetFinalScore() const { return Result.Score; }

private:
	UPROPERTY()
	FMinigameResult Result;
};
