// Copyright LiberiumProject. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "LiberiumProjrct/UI/ViewModel/LiberiumViewModelBase.h"
#include "PauseMenuViewModel.generated.h"

UCLASS(BlueprintType)
class LIBERIUMPROJRCT_API UPauseMenuViewModel : public ULiberiumViewModelBase
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "Pause")
	bool GetIsPaused() const { return bIsPaused; }

	UFUNCTION(BlueprintCallable, Category = "Pause")
	void TogglePause();

	UFUNCTION(BlueprintCallable, Category = "Pause")
	void ResumeGame();

	UFUNCTION(BlueprintCallable, Category = "Pause")
	void QuitToTown();

private:
	bool bIsPaused = false;
};
