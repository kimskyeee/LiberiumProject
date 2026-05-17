// Copyright LiberiumProject. All Rights Reserved.

#include "UI/View/LiberiumWidgetBase.h"
#include "UI/ViewModel/LiberiumViewModelBase.h"

void ULiberiumWidgetBase::SetViewModel(ULiberiumViewModelBase* InViewModel)
{
	if (ViewModel)
	{
		UnbindViewModel();
	}

	ViewModel = InViewModel;

	if (ViewModel)
	{
		BindViewModel();
	}
}

void ULiberiumWidgetBase::BindViewModel()
{
}

void ULiberiumWidgetBase::UnbindViewModel()
{
}
