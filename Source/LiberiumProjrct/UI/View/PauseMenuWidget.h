// Copyright LiberiumProject. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UI/View/LiberiumWidgetBase.h"
#include "PauseMenuWidget.generated.h"

class UButton;
class UPauseMenuViewModel;

UCLASS()
class LIBERIUMPROJRCT_API UPauseMenuWidget : public ULiberiumWidgetBase
{
	GENERATED_BODY()

protected:
	virtual void BindViewModel() override;
	virtual void UnbindViewModel() override;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> ResumeButton;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> QuitButton;

private:
	UFUNCTION()
	void OnResumeClicked();

	UFUNCTION()
	void OnQuitClicked();

	UPauseMenuViewModel* GetPauseViewModel() const;
};
