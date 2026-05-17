// Copyright LiberiumProject. All Rights Reserved.

#include "UI/View/GameOverWidget.h"
#include "UI/ViewModel/GameOverViewModel.h"
#include "UI/Model/MinigameResult.h"
#include "Components/TextBlock.h"

void UGameOverWidget::BindViewModel()
{
	Super::BindViewModel();

	if (ViewModel)
	{
		ViewModel->OnViewModelUpdated.AddDynamic(this, &UGameOverWidget::OnViewModelUpdated);
		OnViewModelUpdated();
	}
}

void UGameOverWidget::UnbindViewModel()
{
	if (ViewModel)
	{
		ViewModel->OnViewModelUpdated.RemoveDynamic(this, &UGameOverWidget::OnViewModelUpdated);
	}

	Super::UnbindViewModel();
}

void UGameOverWidget::OnViewModelUpdated()
{
	UGameOverViewModel* VM = GetGameOverViewModel();
	if (!VM)
	{
		return;
	}

	const FMinigameResult& Result = VM->GetResult();

	if (GameNameText)
	{
		GameNameText->SetText(Result.GameName);
	}

	if (FinalScoreText)
	{
		FinalScoreText->SetText(FText::Format(FText::FromString(TEXT("Score: {0}")), FText::AsNumber(Result.Score)));
	}

	if (ExtraInfoText)
	{
		FString ExtraStr;
		for (const auto& Pair : Result.ExtraFields)
		{
			if (!ExtraStr.IsEmpty())
			{
				ExtraStr += TEXT("\n");
			}
			ExtraStr += FString::Printf(TEXT("%s: %s"), *Pair.Key, *Pair.Value.ToString());
		}
		ExtraInfoText->SetText(FText::FromString(ExtraStr));
	}
}

UGameOverViewModel* UGameOverWidget::GetGameOverViewModel() const
{
	return Cast<UGameOverViewModel>(ViewModel);
}
