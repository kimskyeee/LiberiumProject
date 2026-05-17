// Copyright LiberiumProject. All Rights Reserved.

#include "LiberiumProjrct/UI/View/StackGameHUDWidget.h"
#include "LiberiumProjrct/UI/ViewModel/StackGameHUDViewModel.h"
#include "Components/TextBlock.h"

void UStackGameHUDWidget::BindViewModel()
{
	Super::BindViewModel();

	if (ViewModel)
	{
		ViewModel->OnViewModelUpdated.AddDynamic(this, &UStackGameHUDWidget::OnViewModelUpdated);
		OnViewModelUpdated();
	}
}

void UStackGameHUDWidget::UnbindViewModel()
{
	if (ViewModel)
	{
		ViewModel->OnViewModelUpdated.RemoveDynamic(this, &UStackGameHUDWidget::OnViewModelUpdated);
	}

	Super::UnbindViewModel();
}

void UStackGameHUDWidget::OnViewModelUpdated()
{
	UStackGameHUDViewModel* HUDViewModel = GetHUDViewModel();
	if (!HUDViewModel)
	{
		return;
	}

	if (ScoreText)
	{
		ScoreText->SetText(FText::AsNumber(HUDViewModel->GetScore()));
	}

	if (BlockCountText)
	{
		BlockCountText->SetText(FText::AsNumber(HUDViewModel->GetBlockCount()));
	}
}

UStackGameHUDViewModel* UStackGameHUDWidget::GetHUDViewModel() const
{
	return Cast<UStackGameHUDViewModel>(ViewModel);
}
