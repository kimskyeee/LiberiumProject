// Copyright LiberiumProject. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UI/ViewModel/LiberiumViewModelBase.h"
#include "StackGameHUDViewModel.generated.h"

class AStackingGameMode;

UCLASS(BlueprintType)
class LIBERIUMPROJRCT_API UStackGameHUDViewModel : public ULiberiumViewModelBase
{
	GENERATED_BODY()

public:
	virtual void Initialize(UWorld* InWorld) override;
	virtual void Deinitialize() override;

	UFUNCTION(BlueprintCallable, Category = "HUD")
	int32 GetScore() const { return Score; }

	UFUNCTION(BlueprintCallable, Category = "HUD")
	int32 GetBlockCount() const { return BlockCount; }

	UFUNCTION(BlueprintCallable, Category = "HUD")
	bool GetIsGameOver() const { return bGameOver; }

private:
	UPROPERTY()
	int32 Score = 0;

	UPROPERTY()
	int32 BlockCount = 0;

	UPROPERTY()
	bool bGameOver = false;

	UFUNCTION()
	void HandleScoreChanged();

	UFUNCTION()
	void HandleGameOver();
};
