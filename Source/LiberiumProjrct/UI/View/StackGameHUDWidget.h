// Copyright LiberiumProject. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UI/View/LiberiumWidgetBase.h"
#include "StackGameHUDWidget.generated.h"

class UTextBlock;
class UStackGameHUDViewModel;

UCLASS()
class LIBERIUMPROJRCT_API UStackGameHUDWidget : public ULiberiumWidgetBase
{
	GENERATED_BODY()

protected:
	virtual void BindViewModel() override;
	virtual void UnbindViewModel() override;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> ScoreText;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> BlockCountText;

private:
	UFUNCTION()
	void OnViewModelUpdated();

	UStackGameHUDViewModel* GetHUDViewModel() const;
};
