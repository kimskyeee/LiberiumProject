// Copyright LiberiumProject. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UI/View/LiberiumWidgetBase.h"
#include "GameOverWidget.generated.h"

class UTextBlock;
class UGameOverViewModel;

UCLASS()
class LIBERIUMPROJRCT_API UGameOverWidget : public ULiberiumWidgetBase
{
	GENERATED_BODY()

protected:
	virtual void BindViewModel() override;
	virtual void UnbindViewModel() override;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> GameNameText;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> FinalScoreText;

	UPROPERTY(meta = (BindWidget), BlueprintReadOnly)
	TObjectPtr<UTextBlock> ExtraInfoText;

private:
	UFUNCTION()
	void OnViewModelUpdated();

	UGameOverViewModel* GetGameOverViewModel() const;
};
