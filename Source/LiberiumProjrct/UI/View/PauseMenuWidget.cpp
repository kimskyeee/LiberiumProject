// Copyright LiberiumProject. All Rights Reserved.

#include "LiberiumProjrct/UI/View/PauseMenuWidget.h"
#include "LiberiumProjrct/UI/ViewModel/PauseMenuViewModel.h"
#include "Components/Button.h"

void UPauseMenuWidget::BindViewModel()
{
	Super::BindViewModel();

	if (ResumeButton)
	{
		ResumeButton->OnClicked.AddDynamic(this, &UPauseMenuWidget::OnResumeClicked);
	}

	if (QuitButton)
	{
		QuitButton->OnClicked.AddDynamic(this, &UPauseMenuWidget::OnQuitClicked);
	}
}

void UPauseMenuWidget::UnbindViewModel()
{
	if (ResumeButton)
	{
		ResumeButton->OnClicked.RemoveDynamic(this, &UPauseMenuWidget::OnResumeClicked);
	}

	if (QuitButton)
	{
		QuitButton->OnClicked.RemoveDynamic(this, &UPauseMenuWidget::OnQuitClicked);
	}

	Super::UnbindViewModel();
}

void UPauseMenuWidget::OnResumeClicked()
{
	if (UPauseMenuViewModel* VM = GetPauseViewModel())
	{
		VM->ResumeGame();
	}
}

void UPauseMenuWidget::OnQuitClicked()
{
	if (UPauseMenuViewModel* VM = GetPauseViewModel())
	{
		VM->QuitToTown();
	}
}

UPauseMenuViewModel* UPauseMenuWidget::GetPauseViewModel() const
{
	return Cast<UPauseMenuViewModel>(ViewModel);
}
